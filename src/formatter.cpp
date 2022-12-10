#include "formatter.hpp"
#include <cstddef>

namespace stf {

std::vector<text_chunk> prepare_to_format(const std::string_view& buffer){
	std::vector<text_chunk> text_chunks;
	text_chunks.push_back({.word_length = 0, .space_length = 0});
	size_t chunk_index = 0;
	size_t buffer_index = 0;
	while (buffer_index < buffer.length()) {
		char c = buffer[buffer_index];
		if (c > ' ') {
			text_chunks[chunk_index].word_length++;
			buffer_index++;
		}
		else if (c > '\0') {
			text_chunks[chunk_index].space_length = 1;
			while (c <= ' ') c = buffer[++buffer_index];
		}
		else break;
	}
	return text_chunks;
}

std::string_view format(const std::string_view& buffer, size_t width) {
	std::vector<text_chunk> text_chunks = prepare_to_format(buffer);
	return "";
}


}


