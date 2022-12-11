#include "formatter.hpp"
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>

namespace stf {

size_t text_chunk::length() const
{
	return word.length() + space_length;
}

std::string text_chunk::format() const
{
	std::string formatted_chunk;
	for (size_t i = 0; i < space_length; i++) {
		formatted_chunk.push_back(' ');
	}
	return formatted_chunk + word;
}

std::vector<text_chunk> prepare_to_format(const std::string_view& buffer){
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
	text_chunks.front().space_length = 0;
	return text_chunks;
}

void print_chunks(const std::vector<text_chunk>& text_chunks)
{
	for (const auto& c : text_chunks) {
		std::cout << c.word << ": " << c.word.length() << ", " << c.space_length << "\n";
	}
}

std::string format_line(std::vector<text_chunk>::const_iterator first, std::vector<text_chunk>::const_iterator last)
{
	std::string line;
	for (auto chunk = first; chunk <= last; chunk++)
	{
		
	}
	return line;
}

std::ostream& format(std::istream& in, std::ostream& out, size_t width) {
	std::stringstream s;
	s << in.rdbuf();
	auto text_chunks = prepare_to_format(s.str());
	if (text_chunks.empty()) {
		return out;
	}
	auto line_begin = text_chunks.begin();
	auto line_end = text_chunks.begin();
	size_t line_length = 0;
	do {
		if (line_end == text_chunks.end()) {
			line_end--;
			out << format_line(line_begin, line_end);
			break;
		}
		else if (line_length < width) {
			line_length += line_end->length();
			line_end++;
			continue;
		}
		else {
			if (line_begin != line_end) {
				line_end--;
			}
			out << format_line(line_begin, line_end);
			line_begin = line_end + 1;
		}
	} while (line_begin < text_chunks.end());
	return out;
}

}


