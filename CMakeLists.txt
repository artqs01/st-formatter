project(stfmt)
cmake_minimum_required(VERSION 3.3)

# set (CMAKE_GENERATOR "Unix Makefiles")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG -g -fsanitize=address -fsanitize=undefined -fno-builtin -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -march=native -O3 -ffast-math -ftree-vectorize")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

add_executable(stfmt
	"${PROJECT_SOURCE_DIR}/src/main.cpp"
	"${PROJECT_SOURCE_DIR}/src/formatter.cpp"
)

target_link_libraries(stfmt PRIVATE m)
target_include_directories(stfmt PRIVATE "${PROJECT_SOURCE_DIR}/src")
