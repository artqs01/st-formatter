#ifndef FROMATTER_HPP
#define FROMATTER_HPP

#include <cstddef>
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
	size_t word_length;
	size_t space_length;
};

std::vector<text_chunk> prepare_to_format(const std::string_view& buffer);
std::string_view format(const std::string_view& buffer, size_t width);

}

#endif
