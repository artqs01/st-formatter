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

std::vector<text_chunk> load_chunks(const std::string_view& buffer) {
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
	size_t space_count = last - first;
	if (!space_count) {
		line += first->word;
		return line;
	}
	size_t missing_spaces = width - chunks_length;
	size_t missing_space_length = missing_spaces / space_count + 1;
	// std::cerr << "\n" << space_count << "\n";
	size_t missing_spaces_after_fill = missing_spaces % space_count;
	// std::cerr << "c len:" << chunks_length << "\tms len: " << missing_space_length << "\tmsaf: " << missing_spaces_after_fill << "\tms: " << missing_spaces << "\n";
	for (auto& chunk = first; chunk < last; chunk++)
	{
		chunk->space_length = missing_space_length;
		if (missing_spaces_after_fill) {
			// std::cerr << "dupa";
			chunk->space_length += 1;
			missing_spaces_after_fill--;
		}
		line += chunk->format();
	}
	// std::cerr << "\n";
	// std::cerr << last->word;
	line += last->word;
	// std::cerr << line.length() << "\n";
	return line;
}

std::vector<text_chunk> split(const text_chunk& word, size_t width)
{
	std::vector<text_chunk> split;

}

std::ostream& format(std::istream& in, std::ostream& out, size_t width) {
	std::stringstream s;
	s << in.rdbuf();
	auto text_chunks = load_chunks(s.str());
	std::vector<text_chunk> split_word;
	// print_chunks(text_chunks);
	auto line_begin = text_chunks.begin();
	auto line_end = text_chunks.begin();
	size_t char_count = 0;
	size_t chunk_count = 0;
	while (line_end != text_chunks.end()) {
		if (line_end->word.length() + char_count + chunk_count < width) {
			chunk_count++;
			char_count += line_end->word.length();
			line_end++;
		}
		// std::cerr << "l len:\t" << line_end->word.length() + char_count + chunk_count << "\n";
		else if (line_end->word.length() == width) {
			out << format_line(line_begin, line_end - 1, width, char_count + chunk_count - 1) << "\n"
				<< line_end->word << "\n";
			char_count = 0;
			chunk_count = 0;
			line_begin = ++line_end;
		}
		else if (line_end->word.length() > width)
		{
			out << format_line(line_begin, line_end - 1, width, char_count + chunk_count - 1) << "\n";
			line_begin = line_end;
			split_word = split(*line_end, width);
			text_chunks.insert(line_end, split_word.begin(), split_word.end());
			print_chunks(text_chunks);
		}
		else {
			out << format_line(line_begin, line_end - 1, width, char_count + chunk_count - 1) << "\n";
			// std::cerr << char_count + chunk_count - 1 << "\n";
			// int i = 0;
			// for (auto& c = line_begin; c <= line_end - 1; c++) {
			// 	std::cerr << i++ << ": " << c->word << "\tdl sl: " << c->word.length() << "\tdl sp: " << c->space_length << "\n";
			// }
			// std::cerr << "\n\n";
			chunk_count = 0;
			char_count = 0;
			line_begin = line_end;
		}
	}
	std::string last_line;
	for (auto& chunk = line_begin; chunk < line_end; chunk++)
		last_line += chunk->format();
	out << last_line;
	return out;
}

}


