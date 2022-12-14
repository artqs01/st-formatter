#include "formatter.hpp"
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>

namespace stf {

size_t text_chunk::length() const {
	return word.length() + space_length;
}

std::string text_chunk::format() const {
	return word + std::string(space_length, ' ');
}

std::vector<text_chunk> prepare_to_format(const std::string_view& buffer) {
	std::vector<text_chunk> text_chunks;
	size_t buffer_index = 0;
	size_t next_space_index;
	char current;
	auto find_white_char = [](char c){ return std::isspace(c); };
	std::string word;
	do {
		current = buffer[buffer_index];
		if (std::isspace(current)) {
			buffer_index++;
			continue;
		}
		else {
			next_space_index = std::find_if(
				buffer.begin() + buffer_index,
				buffer.end(),
				find_white_char) - buffer.begin();
			word = buffer.substr(buffer_index, next_space_index - buffer_index);
			buffer_index = next_space_index;
			text_chunks.push_back({.word = word, .space_length = 1});
		}
	} while (buffer_index < buffer.length());
	return text_chunks;
}

void print_chunks(const std::vector<text_chunk>& text_chunks) {
	for (const auto& c : text_chunks) {
		std::cout << c.word << ": " << c.word.length() << ", " << c.space_length << "\n";
	}
}

std::string format_line(
	std::vector<text_chunk>::iterator first,
	std::vector<text_chunk>::iterator last,
	size_t width,
	size_t chunks_length) {
	std::string line;
	size_t missing_spaces = width - chunks_length;
	size_t missing_space_length = missing_spaces / (last - first);
	size_t missing_spaces_after_fill = missing_spaces % (last - first);
	for (auto& chunk = first; chunk < last; chunk++)
	{
		chunk->space_length = missing_space_length;
		if (missing_spaces_after_fill) {
			chunk->space_length += 1;
			missing_space_length--;
		}
		line += chunk->format();
	}
	line += last->word;
	return line;
}

// size_t line_length(
// 	std::vector<text_chunk>::iterator first,
// 	std::vector<text_chunk>::iterator last) {
// 	size_t length = 0;
// 	for (auto& chunk = first; chunk < last; chunk++)
// 	{
// 		length += chunk->length();
// 	}
// 	length += last->word.length();
// 	return length;
// }

std::ostream& format(std::istream& in, std::ostream& out, size_t width) {
	std::stringstream s;
	s << in.rdbuf();
	auto text_chunks = prepare_to_format(s.str());
	auto line_begin = text_chunks.begin();
	auto line_end = text_chunks.begin();
	size_t char_count = 0;
	size_t chunk_count = 0;
	while (line_end != text_chunks.end()) {
		if (line_end->word.length() + char_count + chunk_count - 1 < width) {
			chunk_count++;
			char_count += line_end->word.length();
			line_end++;
		}
		else {
			out << format_line(line_begin, line_end, width, char_count + chunk_count - 1) << "\n";
			chunk_count = 0;
			char_count = 0;
			line_begin = line_end;
		}
	}
	return out;
}

}


