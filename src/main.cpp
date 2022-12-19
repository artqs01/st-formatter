#include "formatter.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    if (argc > 0) {
        std::ifstream f(argv[1]);
        stf::format(f, std::cout, 50);
    }
}
