// Copyright (c) 2024 Dawid Kurek <dawikur@gmail.com>

#include <qrd.hpp>

// ////////////////////////////////////////////////////////////////////////////

qrd::Input test_input {
	"xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))"
};

// ////////////////////////////////////////////////////////////////////////////

enum class Step {
	Begin,
	M,
	U,
	L,
	OpenParen,
	FirstDigit,
	Comma,
	SecondDigit,
	CloseParen
};

int part_one (qrd::Input const& input)
{
	int result{};

	Step step{Step::Begin};
	int first_digit{};
	int second_digit{};
	for (auto const& line: input) {
		for (auto const ch: line) {
			switch (step) {
				case Step::Begin:
					if (ch == 'm') {
						step = Step::M;
					}
					break;
				case Step::M:
					if (ch == 'u') {
						step = Step::U;
					} else {
						step = Step::Begin;
					}
					break;
				case Step::U:
					if (ch == 'l') {
						step = Step::L;
					} else {
						step = Step::Begin;
					}
					break;
				case Step::L:
					if (ch == '(') {
						step = Step::OpenParen;
					} else {
						step = Step::Begin;
					}
					break;
				case Step::OpenParen:
					if (std::isdigit(ch)) {
						step = Step::FirstDigit;
						first_digit = ch - '0';
					} else {
						step = Step::Begin;
					}
					break;
				case Step::FirstDigit:
					if (std::isdigit(ch)) {
						first_digit *= 10;
						first_digit += ch - '0';
					} else if (ch == ',') {
						step = Step::Comma;
					} else {
						step = Step::Begin;
					}
					break;
				case Step::Comma:
					if (std::isdigit(ch)) {
						step = Step::SecondDigit;
						second_digit = ch - '0';
					} else {
						step = Step::Begin;
					}
					break;
				case Step::SecondDigit:
					if (std::isdigit(ch)) {
						second_digit *= 10;
						second_digit += ch - '0';
					} else if (ch == ')') {
						step = Step::CloseParen;
						result += first_digit * second_digit;
					} else {
						step = Step::Begin;
					}
					break;
				case Step::CloseParen:
					if (ch == 'm') {
						step = Step::M;
					} else {
						step = Step::Begin;
					}
					break;
			}
		}
	}

	std::cout << result << std::endl;

    return 0;
}

// ////////////////////////////////////////////////////////////////////////////

void eat (std::string_view& str) {
	str = str.substr(1);
}

bool eat (std::string_view& str, char const ch)
{
	if (str.front() == ch) {
		str = str.substr(1);
		return true;
	}

	return false;
}

bool eat (std::string_view& str, std::string const& chs)
{
	for (auto const ch: chs) {
		if (!eat(str, ch)) {
			return false;
		}
	}

	return true;
}

bool eat (std::string_view& str, int& num)
{
	if (!std::isdigit(str.front())) {
		return false;
	}

	while (std::isdigit(str.front())) {
		num *= 10;
		num += str.front() - '0';
		str = str.substr(1);
	}

	return true;
}

int part_two (qrd::Input const& input)
{
	int result{};
	bool enabled{true};

	for (auto const& line: input) {
		auto str = std::string_view{line};

		while (!str.empty()) {
			int first_number{};
			int second_number{};

			if (eat (str, "mul(")
				&& eat (str, first_number)
				&& eat (str, ',')
				&& eat (str, second_number)
				&& eat (str, ')')) {

				if (enabled) {
					result += first_number * second_number;
				}
			} else if (eat (str, "do")) {
				if (eat (str, "()")) {
					enabled = true;
				} else if (eat (str, "n\'t()")) {
					enabled = false;
				}
			} else {
				eat(str);
			}
		}
	}

	std::cout << result << std::endl;

    return 0;
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

    return ((args->part == qrd::Args::Part::One) ? part_one : part_two) (input);
}
