cmake_minimum_required(VERSION 3.27)
project(jdashdash_modern_parser)

set(CMAKE_CXX_STANDARD 23)

add_executable(jdashdash_modern_parser main.cpp
        Lexers/Lexer/Lexer.cpp
        Lexers/Lexer/Lexer.h
        Lexers/MathLexer/MathLexer.cpp
        Lexers/MathLexer/MathLexer.h
        Parser/Parser.cpp
        Parser/Parser.h
        Definitions/Data/Data.cpp
        Definitions/Data/Data.h
        Definitions/Variable/Variable.cpp
        Definitions/Variable/Variable.h
        Definitions/Types/Types.h
        Definitions/Value/Value.h
        Lexers/VariableReplacementLexer/VariableRepLexer.cpp
        Lexers/VariableReplacementLexer/VariableRepLexer.h
        Definitions/Value/Value.cpp
        Expecter/Expecter.cpp
        Expecter/Expecter.h)
