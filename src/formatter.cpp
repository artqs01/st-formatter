#include "formatter.hpp"
#include <cctype>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

namespace stf {

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
	return text_chunks;
}

void print_chunks(const std::vector<text_chunk>& text_chunks)
{
	for (const auto& c : text_chunks) {
		std::cout << c.word << c.word.length() << ", " << c.space_length << "\n";
	}
}

std::ostream& format(std::istream& in, std::ostream& out, size_t width) {
	std::stringstream s;
	s << in.rdbuf();
	std::vector<text_chunk> text_chunks = prepare_to_format(s.str());
	print_chunks(text_chunks);
	return out << "";
}


}


