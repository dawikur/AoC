// Copyright (c) 2024 Dawid Kurek <dawikur@gmail.com>

#pragma once

namespace qrd {

struct Args {
	enum class Input {
		Test,
		File,
	};

	enum class Part {
		One,
		Two,
	};

	Input input;
	Part part;
};

void print_usage(int const /*argc*/, char const* const argv[]) {
	std::cerr << "Usage: " << argv[0] << " [input] [part]\n";
	std::cerr << "\n";
	std::cerr << "input:\n";
	std::cerr << "    -t, --test       test_input\n";
	std::cerr << "    -f, --file       file input\n";
	std::cerr << "part:\n";
	std::cerr << "    1\n";
	std::cerr << "    2\n";
}

std::optional<Args> parse_args (int const argc, char const* const argv[])
{
	if (argc == 1) {
		return Args{Args::Input::Test, Args::Part::One};
	}

	if (argc != 3) {
		print_usage(argc, argv);
		return {};
	}

	auto result = Args {};

	if (argv[1] == std::string_view{"-t"} || argv[1] == std::string_view{"--test"}) {
		result.input = Args::Input::Test;
	} else if (argv[1] == std::string_view{"-f"} || argv[1] == std::string_view{"--file"}) {
		result.input = Args::Input::File;
	} else {
		std::cerr << "Unknown input: '" << argv[1] << "'\n";
		std::cerr << "\n";
		print_usage(argc, argv);
		return {};
	}

	if (argv[2] == std::string_view{"1"}) {
		result.part = Args::Part::One;
	} else if (argv[2] == std::string_view{"2"}) {
		result.part = Args::Part::Two;
	} else {
		std::cerr << "Unknown part: '" << argv[2] << "'\n";
		std::cerr << "\n";
		print_usage(argc, argv);
		return {};
	}

	return result;
}

} // namespace qrd
