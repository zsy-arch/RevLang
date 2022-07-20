cmake_minimum_required(VERSION 3.22)
project(RevLang)

set(CMAKE_CXX_STANDARD 14)

add_executable(RevLang main.cpp core/Lexer.cpp core/Lexer.h core/Token.cpp core/Token.h)
