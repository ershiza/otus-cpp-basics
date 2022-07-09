cmake_minimum_required(VERSION 3.5)

project(guess_the_number)

add_executable(
	guess_the_number
	guess_the_number.cpp
    parse_arg.cpp
    parse_arg.h
    io_score.cpp
    io_score.h
    game.cpp
    game.h
)

set_target_properties(guess_the_number PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)