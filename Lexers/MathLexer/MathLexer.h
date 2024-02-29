#pragma once

#include <iostream>
#include <algorithm>
#include "../Lexer/Lexer.h"

namespace JDD::Lexer::Math {
    std::pair<bool, int> haveMul(const std::vector<Token>& tokenList);
    std::pair<bool, int> haveDiv(const std::vector<Token>& tokenList);
    std::pair<bool, int> haveAdd(std::vector<Token>& tokenList);
    std::pair<bool, int> haveSub(std::vector<Token>& tokenList);
    std::pair<double, double> getNumbers(std::vector<Token>& tokenList, int index);
    void Lexer(std::vector<Token>& tokenList);
}