cmake_minimum_required(VERSION 3.10)
project(cpp-tknizer)

set(CMAKE_CXX_STANDARD 17)

# Add the MLC tokenizer as a subdirectory
add_subdirectory(tokenizers-cpp)

# Add your source files
add_executable(tknizer main.cpp)

# Link the tokenizer library
target_link_libraries(tknizer tokenizers_cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)
