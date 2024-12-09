// Copyright (c) 2024 Dawid Kurek <dawikur@gmail.com>

#include <qrd.hpp>

// ////////////////////////////////////////////////////////////////////////////

qrd::Input test_input_one {
	"2333133121414131402",
};

qrd::Input test_input_two = test_input_one;

// ////////////////////////////////////////////////////////////////////////////

int from_ch(char ch) {
	return ch - '0';
}

void part_one (qrd::Input const& input)
{
	std::vector<int> disk;

	int ID{};
	bool is_file{true};
	for (auto ch: input[0]) {
		for (int i = 0; i < ch - '0'; ++i) {
			disk.push_back(is_file ? ID : -1);
		}

		if (is_file) {
			++ID;
		}

		is_file = !is_file;
	}

	//for (auto const block : disk) {
	//	if (block != -1) {
	//		auto const ratio = static_cast<float> (block+1) / static_cast<float> (ID * 2);
	//		auto const rgb = qrd::RGB::from_1D (ratio);
	//		std::cout << qrd::term (rgb);
	//	}

	//	std::cout << "▓";
	//	std::cout << qrd::term();
	//}
	//std::cout << std::endl;

	std::size_t lhs{};
	std::size_t rhs{disk.size()-1};

	while (lhs < rhs) {
		if (disk[lhs] != -1) {
			++lhs;
		} else if (disk[rhs] == -1) {
			--rhs;
		} else {
			std::swap (disk[lhs], disk[rhs]);
			++lhs;
			--rhs;

		}
	}

	std::size_t checksum{};
	for (std::size_t i = 0; i < disk.size(); ++i) {
		if (disk[i] != -1) {
			checksum += i * static_cast<std::size_t>(disk[i]);
		}
	}

	std::cout << checksum << std::endl;
}

// ////////////////////////////////////////////////////////////////////////////

void print (std::vector<int> const& disk)
{
			for (auto const block : disk) {
				if (block != -1) {
					auto const ratio = static_cast<float> (block+1) / static_cast<float> (disk.size());
					auto const rgb = qrd::RGB::from_1D (ratio);
					std::cout << qrd::term (rgb);
				}

				std::cout << "▓";
				std::cout << qrd::term();
			}
			std::cout << std::endl;
}

void part_two (qrd::Input const& input)
{
	std::vector<int> disk;

	int ID{};
	bool is_file{true};
	for (auto ch: input[0]) {
		for (int i = 0; i < ch - '0'; ++i) {
			disk.push_back(is_file ? ID : -1);
		}

		if (is_file) {
			++ID;
		}

		is_file = !is_file;
	}

	//print (disk);

	for (std::size_t block {disk.size () - 1}; 0 < block;) {
		if (disk[block] == -1) {
			--block;
			continue;
		}

		std::size_t block_size{};
		for (std::size_t i = block; 0 < i; --i) {
			if (disk[i] != disk[block]) {
				break;
			}
			++block_size;
		}

		for (std::size_t free{}; free < block; ++free) {
			if (disk[free] != -1) {
				continue;
			}

			std::size_t free_size{};
			for (std::size_t i = free; i < block; ++i) {
				if (disk[i] != -1) {
					break;
				}
				++free_size;
			}

			if (block_size <= free_size) {
				std::size_t moved{};
				while (moved < block_size) {
					std::swap(disk[free+moved], disk[block-moved]);
					++moved;
				}

				//print (disk);
				break;
			}
		}

		block -= block_size;
	}

	std::size_t checksum{};
	for (std::size_t i = 0; i < disk.size(); ++i) {
		if (disk[i] != -1) {
			checksum += i * static_cast<std::size_t>(disk[i]);
		}
	}

	std::cout << checksum << std::endl;
}

// ////////////////////////////////////////////////////////////////////////////

int main (int const argc, char const* const argv[])
{
    auto const args = qrd::parse_args (argc, argv);

    if (!args) {
        return 1;
    }

	auto input = (args->input == qrd::Args::Input::File)
				   ? qrd::read_file (__FILE__)
				   : ((args->part == qrd::Args::Part::One) ? test_input_one
														   : test_input_two);

	if (args->part == qrd::Args::Part::One){
		part_one(input);
	} else {
		part_two(input);
	}

    return 0;
}
