#include "formatter.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
	if (argc > 0) {
		std::ifstream f(argv[1]);
		// stf::format_fill(f, std::cout, 10);
		stf::format_wrap_text(f, std::cout, 7);
	}
}
