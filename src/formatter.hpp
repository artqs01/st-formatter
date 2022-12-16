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

// Represents single word from a text and space length after word
struct text_chunk
{
	std::string word;

	// Lenghth od a space after word
	size_t space_length;

	size_t length() const;

	// Returns formated text chunk
	std::string format() const;
};

std::vector<text_chunk> load_chunks(const std::string_view& buffer);
std::string format_line(
	std::vector<text_chunk>::iterator first,
	std::vector<text_chunk>::iterator last,
	size_t width,
	size_t chunks_length);
std::vector<text_chunk> split(const text_chunk& word);
std::ostream& format(std::istream& in, std::ostream& out, size_t width);
void print_chunks(const std::vector<text_chunk>& text_chunks);

}

#endif
