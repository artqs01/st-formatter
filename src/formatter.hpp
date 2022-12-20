#ifndef FROMATTER_HPP
#define FROMATTER_HPP

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <sstream>
#include <string>
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
	size_t space_size;

	size_t length() const;

	// Returns formated text chunk
	std::string format() const;
};

std::vector<text_chunk> load_chunks(const std::string_view& buffer, const size_t space_size);
std::string format_line_fill(
	std::vector<text_chunk>& text_chunks,
	size_t begin_index,
	size_t end_index,
	size_t width,
	size_t chunks_length);
std::vector<text_chunk> split(const text_chunk& word);
std::ostream& format_fill(std::istream& in, std::ostream& out, const size_t width);
std::ostream& format_wrap_text(std::istream& in, std::ostream& out, const size_t width);

// debug functions
void print_chunks(const std::vector<text_chunk>& text_chunks);

}

#endif
