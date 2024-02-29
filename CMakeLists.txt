cmake_minimum_required(VERSION 3.27)
project(jdashdash_modern_parser)

set(CMAKE_CXX_STANDARD 23)

add_executable(jdashdash_modern_parser main.cpp
        Lexer/Lexer.cpp
        Lexer/Lexer.h
        MathLexer/MathLexer.cpp
        MathLexer/MathLexer.h)
