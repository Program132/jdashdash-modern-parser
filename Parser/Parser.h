#pragma once

#include <iostream>
#include <vector>
#include "../Lexers/Lexer/Lexer.h"
#include "../Definitions/Data/Data.h"
#include "../Definitions/Variable/Variable.h"
#include "../Definitions/Value/Value.h"
#include "../Expecter/Expecter.h"

using namespace JDD::Definitions;
using namespace JDD::Lexer;

namespace JDD::Parser {
    void run(std::vector<Token> tokensList);
    bool instructionsManagement(Data& data, std::vector<JDD::Lexer::Token>& tokensList, std::vector<Token>::iterator& current);

    void basicVariableDeclaration(Data& data, std::vector<JDD::Lexer::Token>& tokensList, std::vector<Token>::iterator& current, JDD::Definitions::Types type);
}