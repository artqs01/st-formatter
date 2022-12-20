#include "formatter.hpp"
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
	size_t width = 40;
	if (argc < 0) {
		std::cout << "No arguments provided! Closing...\n";
		return -1;
	}
	else {
		if (!argv[2])
		{
			std::cout << "To few arguments provided! Closing...\n";
			return -1;
		}
		else if (argv[2][0] != '.' && argv[2][0] != '/') {
			std::cout << "No file directory provided! Closing...\n";
			return -1;
		}
		if (argv[3] && argv[4]) {
			if (std::string(argv[3]) == "-width") {
				width = atoi(argv[4]);
			}
			else {
				std::cout << "Wrong flags provided! Closing...\n";
				return -1;
			}
		}
		std::ifstream f(argv[2]);
		if (std::string(argv[1]) == "-wrap") {
			stf::format_wrap_text(f, std::cout, width);
		}
		else if (std::string(argv[1]) == "-fill") {
			stf::format_fill(f, std::cout, width);
		}
		else {
			std::cout << "Wrong flags provided! Closing...\n";
			return -1;
		}
	}
}
