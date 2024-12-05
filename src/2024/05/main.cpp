// Copyright (c) 2024 Dawid Kurek <dawikur@gmail.com>

#include <qrd.hpp>

// ////////////////////////////////////////////////////////////////////////////

qrd::Input test_input {
	"47|53",
	"97|13",
	"97|61",
	"97|47",
	"75|29",
	"61|13",
	"75|53",
	"29|13",
	"97|29",
	"53|29",
	"61|53",
	"97|53",
	"61|29",
	"47|13",
	"75|47",
	"97|75",
	"47|61",
	"75|61",
	"47|29",
	"75|13",
	"53|13",
	"",
	"75,47,61,53,29",
	"97,61,53,29,13",
	"75,29,13",
	"75,97,47,61,53",
	"61,13,29",
	"97,13,75,29,47",
};

// ////////////////////////////////////////////////////////////////////////////

bool is_rule_broken (
	std::unordered_map<std::size_t, std::unordered_set<std::size_t>>& rules,
	std::size_t                                                       lhs,
	std::size_t                                                       rhs)
{
	for (auto const page: rules[lhs]) {
		if (rhs == page) {
			return true;
		}
	}

	return false;
}

void part_one (qrd::Input const& input)
{
	std::size_t result{0};

	std::unordered_map<std::size_t, std::unordered_set<std::size_t>> rules;

	bool first{true};
    for (auto const& line : input) {
		if (line.empty()) {
			first = false;
		} else if (first) {
			auto const pages = qrd::split_as<std::size_t>(line, '|');
			rules[pages[0]].emplace(pages[1]);
		} else {
			std::cout << line << std::endl;
			auto const pages= qrd::split_as<std::size_t>(line, ',');

			bool is_correct{true};
			for (std::size_t i = 1; i < pages.size(); ++i) {
				auto const lhs = pages[i-1];
				auto const rhs = pages[i];

				for (auto const rule: rules[rhs]) {
					if (rule == lhs) {
						is_correct = false;
						std::cout << "    rule " << rhs << "|" << rule << std::endl;
					}
				}
			}

			if (is_correct) {
				std::cout << pages[(pages.size()) / 2] << std::endl;
				result += pages[(pages.size()) / 2];
			}
		}
	}

	std::cout << result << std::endl;
}

// ////////////////////////////////////////////////////////////////////////////

void part_two (qrd::Input const& input)
{
	std::size_t result{0};

	std::unordered_map<std::size_t, std::unordered_set<std::size_t>> rules;

	bool first{true};
    for (auto const& line : input) {
		if (line.empty()) {
			first = false;
		} else if (first) {
			auto const pages = qrd::split_as<std::size_t>(line, '|');
			rules[pages[0]].emplace(pages[1]);
		} else {
			auto updates= qrd::split_as<std::size_t>(line, ',');

			bool is_correct{true};

			for (std::size_t i = 1; i < updates.size(); ++i) {
				for (std::size_t k{i}; 0 < k; --k) {
					bool modified = false;

					for (auto const rule: rules[updates[k]]) {
						if (rule == updates[k-1]) {
							is_correct = false;
							modified = true;
							std::swap(updates[k-1], updates[k]);

							std::cout << "  [";
							for (std::size_t j = 0U; j < updates.size (); ++j) {
								if (j != 0U) {
									std::cout << ",";
								}

								if (j == k || j == k-1) {
									std::cout << qrd::term(qrd::Csi::Bold);
								}

								std::cout << updates [j];
								std::cout << qrd::term();
							}
							std::cout << ']' << std::endl;
						}
					}

					if (!modified) {
						break;
					}
				}
			}

			if (!is_correct) {
				auto const middle = (updates.size()) / 2;

				std::cout << "+ [";
				for (std::size_t j = 0U; j < updates.size (); ++j) {
					if (j != 0U) {
						std::cout << ",";
					}

					if (j == middle) {
						std::cout << qrd::term(qrd::Csi::Blue);
						std::cout << qrd::term(qrd::Csi::Bold);
					}

					std::cout << updates [j];
					std::cout << qrd::term();
				}
				std::cout << ']' << std::endl;
				result += updates[(updates.size()) / 2];
			}
		}
	}

	auto const result_str = std::to_string(result);
	std::cout << "  " << std::string(result_str.size(), '=') << std::endl;
	std::cout << "  " << result_str << std::endl;
}

// ////////////////////////////////////////////////////////////////////////////

int main (int const argc, char const* const argv[])
{
    auto const args = qrd::parse_args (argc, argv);

    if (!args) {
        return 1;
    }

    auto const input = (args->input == qrd::Args::Input::File)
                         ? qrd::read_input (__FILE__)
                         : test_input;

    ((args->part == qrd::Args::Part::One) ? part_one : part_two) (input);

	return 0;
}
