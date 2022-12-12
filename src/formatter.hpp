#ifndef FROMATTER_HPP
#define FROMATTER_HPP

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string_view>
#include <utility>
#include <vector>

namespace stf
{

// Represents single word from a text and space length before actual word
struct text_chunk
{
	std::string word;

	// lenghth od a space before actual word
	size_t space_length;

	size_t length() const;
	std::string format() const;
};

std::vector<text_chunk> prepare_to_format(const std::string_view& buffer);
std::string format_line(
	std::vector<text_chunk>::const_iterator first,
	std::vector<text_chunk>::const_iterator last,
	size_t width);
std::ostream& format(std::istream& in, std::ostream& out, size_t width, size_t chunks_length);
void print_chunks(const std::vector<text_chunk>& text_chunks);

}

#endif
