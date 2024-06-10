#include "MathLexer.h"

namespace JDD::Lexer::Math {
    std::pair<bool, int> haveMul(const std::vector<Token>& tokenList) {
        for (int i = 0; i < tokenList.size()-1; ++i) {
            if (tokenList[i].type == OPERATOR && tokenList[i].content == "*" && tokenList[i+1].content != "=") {
                return {true, i};
            }
        }
        return {false, -1};
    }

    std::pair<bool, int> haveDiv(const std::vector<Token>& tokenList) {
        for (int i = 0; i < tokenList.size()-1; ++i) {
            if (tokenList[i].type == OPERATOR && tokenList[i].content == "/" && tokenList[i+1].content != "=") {
                return {true, i};
            }
        }
        return {false, -1};
    }

    std::pair<bool, int> haveAdd(std::vector<Token>& tokenList) {
        for (int i = 0; i < tokenList.size()-1; ++i) {
            if (tokenList[i].type == OPERATOR && tokenList[i].content == "+" && tokenList[i+1].content != "=") {
                return {true, i};
            }
        }
        return {false, -1};
    }

    std::pair<bool, int> haveSub(std::vector<Token>& tokenList) {
        for (int i = 0; i < tokenList.size()-1; ++i) {
            if (tokenList[i].type == OPERATOR && tokenList[i].content == "-" && tokenList[i+1].content != "=") {
                return {true, i};
            }
        }
        return {false, -1};
    }

    std::pair<double, double> getNumbers(std::vector<Token>& tokenList, int index) {
        // x <op> y, x = l & y = r & <op> = operation (add, sub, etc.)
        Token l = tokenList[index-1];
        Token r = tokenList[index+1];
        if ((l.type != INT && l.type != DOUBLE) || (r.type != INT && r.type != DOUBLE)) {
            std::cerr << "Error: The lexer is not over due to a Math problem in your code (type problem), line " << r.line << std::endl;
            exit(0);
        }
        return {std::stoi(l.content), std::stoi(r.content)};
    }

    void Lexer(std::vector<Token>& tokenList) {
        auto current_token = tokenList.begin();

        while (current_token != tokenList.end()) {
            auto possibleMul = haveMul(tokenList);
            while (possibleMul.first) {
                auto nums = getNumbers(tokenList, possibleMul.second);
                double result = nums.first * nums.second;
                Token l = tokenList[possibleMul.second-1];
                Token r = tokenList[possibleMul.second+1];

                // Deleting + replacing
                tokenList[possibleMul.second].content = std::to_string(result);
                if (l.type == INT) {
                    tokenList[possibleMul.second].type = INT;
                    tokenList[possibleMul.second].content = std::to_string(std::stoi(tokenList[possibleMul.second].content));
                } else {
                    tokenList[possibleMul.second].type = DOUBLE;
                }
                if (possibleMul.second - 1 >= 0 && possibleMul.second + 1 < tokenList.size()) {
                    tokenList.erase(tokenList.begin() + possibleMul.second - 1);
                    tokenList.erase(tokenList.begin() + possibleMul.second);
                }

                possibleMul = haveMul(tokenList);
            }

            auto possibleDiv = haveDiv(tokenList);
            while (possibleDiv.first) {
                auto nums = getNumbers(tokenList, possibleDiv.second);
                double result = nums.first / nums.second;
                Token l = tokenList[possibleDiv.second-1];
                Token r = tokenList[possibleDiv.second+1];

                // Deleting + replacing
                tokenList[possibleDiv.second].content = std::to_string(result);
                if (l.type == INT) {
                    tokenList[possibleDiv.second].type = INT;
                    tokenList[possibleDiv.second].content = std::to_string(std::stoi(tokenList[possibleDiv.second].content));
                } else {
                    tokenList[possibleMul.second].type = DOUBLE;
                }
                if (possibleDiv.second - 1 >= 0 && possibleDiv.second + 1 < tokenList.size()) {
                    tokenList.erase(tokenList.begin() + possibleDiv.second - 1);
                    tokenList.erase(tokenList.begin() + possibleDiv.second);
                }

                possibleDiv = haveDiv(tokenList);
            }

            auto possibleAdd = haveAdd(tokenList);
            while (possibleAdd.first) {
                auto nums = getNumbers(tokenList, possibleAdd.second);
                double result = nums.first + nums.second;
                Token l = tokenList[possibleAdd.second-1];
                Token r = tokenList[possibleAdd.second+1];

                // Deleting + replacing
                tokenList[possibleAdd.second].content = std::to_string(result);
                if (l.type == INT) {
                    tokenList[possibleAdd.second].type = INT;
                    tokenList[possibleAdd.second].content = std::to_string(std::stoi(tokenList[possibleAdd.second].content));
                } else {
                    tokenList[possibleAdd.second].type = DOUBLE;
                }
                if (possibleAdd.second - 1 >= 0 && possibleAdd.second + 1 < tokenList.size()) {
                    tokenList.erase(tokenList.begin() + possibleAdd.second - 1);
                    tokenList.erase(tokenList.begin() + possibleAdd.second);
                }

                possibleAdd = haveAdd(tokenList);
            }

            auto possibleSub = haveSub(tokenList);
            while (possibleSub.first) {
                auto nums = getNumbers(tokenList, possibleSub.second);
                double result = nums.first - nums.second;
                Token l = tokenList[possibleSub.second-1];
                Token r = tokenList[possibleSub.second+1];

                // Deleting + replacing
                tokenList[possibleSub.second].content = std::to_string(result);
                if (l.type == INT) {
                    tokenList[possibleSub.second].type = INT;
                    tokenList[possibleSub.second].content = std::to_string(std::stoi(tokenList[possibleSub.second].content));
                } else {
                    tokenList[possibleSub.second].type = DOUBLE;
                }
                if (possibleSub.second - 1 >= 0 && possibleSub.second + 1 < tokenList.size()) {
                    tokenList.erase(tokenList.begin() + possibleSub.second - 1);
                    tokenList.erase(tokenList.begin() + possibleSub.second);
                }

                possibleSub = haveMul(tokenList);
            }

            ++current_token;
        }
    }
}