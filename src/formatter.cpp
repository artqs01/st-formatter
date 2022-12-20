#include "formatter.hpp"
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
#include <cassert>

namespace stf {

size_t text_chunk::length() const
{
	return word.length() + space_length;
}

std::string text_chunk::format() const
{
	return word + std::string(space_length, ' ');
}

std::vector<text_chunk> load_chunks(const std::string_view& buffer)
{
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
				find_white_char
			) - buffer.begin();
			word = buffer.substr(buffer_index, next_space_index - buffer_index);
			buffer_index = next_space_index;
			text_chunks.push_back({.word = word, .space_length = 1});
		}
	} while (buffer_index < buffer.length());
	text_chunks.back().space_length = 0;
	return text_chunks;
}

std::string format_line(
	std::vector<text_chunk>& text_chunks,
	size_t line_begin,
	size_t last,
	size_t width,
	size_t chunks_length)
{
	assert(chunks_length <= width);
	assert(last >= line_begin);
	std::string line;
	if (last == line_begin) {
		line += text_chunks[last].word;
		return line;
	}
	size_t space_count = last - line_begin;
	size_t missing_spaces = width - chunks_length;
	size_t missing_space_length = missing_spaces / space_count + 1;
	size_t missing_spaces_after_fill = missing_spaces % space_count;
	for (size_t i = line_begin; i < last; i++)
	{
		text_chunks[i].space_length = missing_space_length;
		if (missing_spaces_after_fill) {
			text_chunks[i].space_length += 1;
			missing_spaces_after_fill--;
		}
		line += text_chunks[i].format();
	}
	line += text_chunks[last].word;
	return line;
}

std::vector<text_chunk> split(const text_chunk& chunk,  const size_t width)
{
	std::vector<text_chunk> split;
	std::string word;
	size_t begin_index = 0;
	size_t step = width - 1;
	for (begin_index = 0; begin_index + step < chunk.word.length(); begin_index += step) {
		word = chunk.word.substr(begin_index, step) + "-";
		split.push_back({.word = word, .space_length = 0});
	}
	word = chunk.word.substr(begin_index);
	split.push_back({.word = word, .space_length = 0});
	return split;
}

void format_big_word(
	std::vector<text_chunk>& text_chunks,
	std::ostream& out,
	const size_t width,
	const size_t line_begin,
	const size_t line_end,
	const size_t chunks_length,
	const size_t end_word_length)
{
	if (line_begin != line_end) {
		out << format_line(text_chunks,
			line_begin,
			line_end - 1,
			width,
			chunks_length - 1
		) << "\n";
	}
	if (end_word_length > width)
	{
		auto split_word = split(text_chunks[line_end], width);
		text_chunks.insert(
			text_chunks.begin() + line_end + 1,
			split_word.begin(),
			split_word.end());
		text_chunks.erase(text_chunks.begin() + line_end);
	}
	out << text_chunks[line_end].word << "\n";
}

std::ostream& format_fill(std::istream& in, std::ostream& out, const size_t width)
{
	std::stringstream s;
	s << in.rdbuf();
	auto text_chunks = load_chunks(s.str());
	assert(!text_chunks.empty());

	size_t line_begin = 0;
	size_t line_end = 0;
	size_t char_count = 0;
	size_t chunk_count = 0;
	size_t chunks_length;
	size_t end_word_length;

	// main loop
	while (line_end != text_chunks.size()) {
		end_word_length = text_chunks[line_end].word.length();
		chunks_length = char_count + chunk_count;
		if (end_word_length + chunks_length < width) {
			char_count += end_word_length;
			chunk_count++;
			line_end++;
		}
		else if (end_word_length >= width)
		{
			format_big_word(
				text_chunks,
				out,
				width,
				line_begin,
				line_end,
				chunks_length,
				end_word_length
			);
			char_count = 0;
			chunk_count = 0;
			line_begin = ++line_end;
		}
		else {
			out << format_line(
				text_chunks,
				line_begin,
				line_end - 1,
				width,
				chunks_length - 1
			) << "\n";
			chunk_count = 0;
			char_count = 0;
			line_begin = line_end;
		}
	}

	// last iteration
	std::string last_line;
	for (size_t i = line_begin; i < line_end; i++)
		last_line += text_chunks[i].format();
	out << last_line;
	return out;
}


void print_chunks(const std::vector<text_chunk>& text_chunks)
{
	for (const auto& c : text_chunks) {
		std::cout << c.word << ": " << c.word.length() << ", " << c.space_length << "\n";
	}
}

}


