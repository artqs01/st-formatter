#ifndef FROMATTER_HPP
#define FROMATTER_HPP

#include <cstddef>
#include <ostream>
#include <string_view>
#include <utility>
#include <vector>

namespace stf
{

// class formatter
// {
// 	public:
// 		formatter(std::string_view directory);
// 	private:
// 		std::filesystem::path directory = "";
// 		std::string file_buf = "";
// };

struct text_chunk
{
	std::string word;
	size_t space_length;
};

std::vector<text_chunk> prepare_to_format(const std::string_view& buffer);
std::ostream& format(std::istream& in, std::ostream& out, size_t width);

}

#endif
