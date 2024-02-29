#include "Parser.h"

namespace JDD::Parser {
    void run(std::vector<JDD::Lexer::Token> tokensList)  {
        Data data;
        auto current = tokensList.begin();

        while (current != tokensList.end()) {
            if (!instructionsManagement(data, tokensList, current)) {
                std::cerr  << "{UNKNOWN} -> " << *current << std::endl;
                ++current;
            }
        }
    }

    bool instructionsManagement(Data& data, std::vector<JDD::Lexer::Token>& tokensList, std::vector<Token>::iterator& current) {
        auto instruction = ExpectIdentifiant(current);

        if (instruction.has_value() && instruction->content == "int") {
            basicVariableDeclaration(data, tokensList, current, JDD::Definitions::Types::INT);
            return true;
        } else if (instruction.has_value() && instruction->content == "double") {
            basicVariableDeclaration(data, tokensList, current, JDD::Definitions::Types::DOUBLE);
            return true;
        } else if (instruction.has_value() && instruction->content == "string") {
            basicVariableDeclaration(data, tokensList, current, JDD::Definitions::Types::STRING);
            return true;
        } else if (instruction.has_value() && instruction->content == "boolean") {
            basicVariableDeclaration(data, tokensList, current, JDD::Definitions::Types::BOOLEAN);
            return true;
        }
        return false;
    }



    void basicVariableDeclaration(Data& data, std::vector<JDD::Lexer::Token>& tokensList, std::vector<Token>::iterator& current, JDD::Definitions::Types type) {
        std::optional<Definitions::Types> var_type = type;
        bool isFinal = false;
        if (type == Definitions::FINAL_NotType) {
            var_type = ExpectType(current);
            isFinal = true;
            if (!var_type.has_value()) {
                std::cerr << "[VARIABLE DECLARATION] Need a type for your variable" << std::endl;
                exit(1);
            }
        }

        if (var_type == Definitions::Types::VOID) {
            std::cerr << "[VARIABLE DECLARATION] A variable can not be void" << std::endl;
            exit(2);
        }

        auto name = ExpectIdentifiant(current);
        if (!name.has_value()) {
            std::cerr << "[VARIABLE DECLARATION] Need the name of your variable, line " << current->line << std::endl;
            exit(3);
        }

        if (!ExpectOperator(current, "=").has_value()) {
            std::cerr << "[VARIABLE DECLARATION] Need '=' operator to give your value, line " << current->line << std::endl;
            exit(4);
        }

        auto value = ExpectValue(current);
        if (!value.has_value()) {
            std::cerr << "[VARIABLE DECLARATION] Need the value of your variable, line " << current->line << std::endl;
            exit(5);
        }

        if (!ExpectOperator(current, ";").has_value()) {
            std::cerr << "[VARIABLE DECLARATION] Need ';' operator to conclude the instruction, line " << current->line << std::endl;
            exit(7);
        }

        if (data.isVariable(name->content)) {
            std::cerr << "[VARIABLE DECLARATION] This variable has been already declared, line " << current->line << std::endl;
            exit(6);
        }

        Variable var;
        var.name = name->content;
        var.type = type;
        var.value = value.value();
        var.isFinal = isFinal;

        data.addVariableToData(var);
    }
}