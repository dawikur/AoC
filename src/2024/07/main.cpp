// Copyright (c) 2024 Dawid Kurek <dawikur@gmail.com>

#include <qrd.hpp>

// ////////////////////////////////////////////////////////////////////////////

qrd::Input test_input {
	"190: 10 19",
	"3267: 81 40 27",
	"83: 17 5",
	"156: 15 6",
	"7290: 6 8 6 15",
	"161011: 16 10 13",
	"192: 17 8 14",
	"21037: 9 7 18 13",
	"292: 11 6 16 20",
};

// ////////////////////////////////////////////////////////////////////////////

using Ops = std::vector<char>;

std::size_t operator_pipe (std::size_t lhs, std::size_t rhs)
{
	auto token = std::to_string(lhs) + std::to_string(rhs);

	std::size_t value {};
	std::from_chars (token.data (), token.data () + token.size (), value);

	return value;
}

Ops try_solve(std::size_t target, std::vector<std::size_t> values)
{
	auto const lhs = values.back();
	values.pop_back();

	auto const rhs = values.back();
	values.pop_back();

	if (values.empty()) {
		if (lhs + rhs == target) {
			return {'+'};
		}

		if (lhs * rhs == target) {
			return {'*'};
		}

		if (operator_pipe(lhs, rhs) == target) {
			return {'|'};
		}

		return {};
	}

	values.push_back(0);

	values.back() = lhs + rhs;
	if (auto ops = try_solve (target, values); !ops.empty ()) {
		ops.push_back('+');
		return ops;
	}

	values.back() = lhs * rhs;
	if (auto ops = try_solve (target, values); !ops.empty ()) {
		ops.push_back('*');
		return ops;
	}

	values.back() = operator_pipe(lhs, rhs);
	if (auto ops = try_solve (target, values); !ops.empty ()) {
		ops.push_back('|');
		return ops;
	}

	return {};
}

void part_one (qrd::Input const& input)
{
	std::size_t sum{};

    for (auto const& line : input) {
		auto const values = qrd::split_as<std::size_t> (line, ' ');

		auto const result = values[0];

		std::vector<std::size_t> tmp;
		for (size_t i = values.size()-1; 0 <i; --i) {
			tmp.push_back (values[i]);
		}


		std::cout << line << std::endl;

		auto const ops = try_solve (result, tmp);

		if (ops.empty()) {
			std::cout << "    No solution" << std::endl;
			continue;
		}

		sum += result;

		std::cout << "    " << tmp.back()<< " ";
		for (size_t i = 0 ; i <ops.size(); ++i) {
			std::cout << ops[ops.size() - i-1] << " " << values[i +2] << " ";
		}
		std::cout << std::endl;

	}

	std::cout << sum << std::endl;
}

// ////////////////////////////////////////////////////////////////////////////

void part_two (qrd::Input const& input)
{
    (void) input;
}

// ////////////////////////////////////////////////////////////////////////////

int main (int const argc, char const* const argv[])
{
    auto const args = qrd::parse_args (argc, argv);

    if (!args) {
        return 1;
    }

    auto const input = (args->input == qrd::Args::Input::File)
                         ? qrd::read_file (__FILE__)
                         : test_input;

    ((args->part == qrd::Args::Part::One) ? part_one : part_two) (input);

    return 0;
}
