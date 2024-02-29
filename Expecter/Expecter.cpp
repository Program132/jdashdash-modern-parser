#include "Expecter.h"

namespace JDD::Parser {
    std::optional<JDD::Lexer::Token> ExpectIdentifiant(std::vector<JDD::Lexer::Token>::iterator& current)  {
        if (current->type == JDD::Lexer::IDENTIFIANT) {
            return *(current++);
        }
        return std::nullopt;
    }

    std::optional<JDD::Definitions::Value> ExpectValue(std::vector<JDD::Lexer::Token>::iterator& current) {
        if (current->type == Lexer::INT) {
            JDD::Definitions::Value v;
            v.content = current->content;
            v.type = JDD::Definitions::Types::INT;
            current++;
            return v;
        } else if (current->type == Lexer::DOUBLE) {
            JDD::Definitions::Value v;
            v.content = current->content;
            v.type = JDD::Definitions::Types::DOUBLE;
            current++;
            return v;
        } if (current->type == Lexer::STRING) {
            JDD::Definitions::Value v;
            v.content = current->content;
            v.type = JDD::Definitions::Types::STRING;
            current++;
            return v;
        } if (current->type == Lexer::BOOL) {
            JDD::Definitions::Value v;
            v.content = current->content;
            v.type = JDD::Definitions::Types::BOOLEAN;
            current++;
            return v;
        }
        return std::nullopt;
    }

    std::optional<JDD::Definitions::Types> ExpectType(std::vector<JDD::Lexer::Token>::iterator& current) {
        if (current->type == JDD::Lexer::IDENTIFIANT) {
            if (current->content == "int") {
                current++;
                return JDD::Definitions::Types::INT;
            } else if (current->content == "double") {
                current++;
                return JDD::Definitions::Types::DOUBLE;
            } else if (current->content == "string") {
                current++;
                return JDD::Definitions::Types::STRING;
            } else if (current->content == "boolean") {
                current++;
                return JDD::Definitions::Types::BOOLEAN;
            } else if (current->content == "final") {
                current++;
                return JDD::Definitions::Types::FINAL_NotType;
            } else if (current->content == "void") {
                current++;
                return JDD::Definitions::Types::VOID;
            }
        }
        return std::nullopt;
    }

    std::optional<JDD::Lexer::Token> ExpectOperator(std::vector<JDD::Lexer::Token>::iterator& current, std::string_view o) {
        if ((current->type == JDD::Lexer::OPERATOR && o.empty())
                || (current->type == JDD::Lexer::OPERATOR && current->content == o)) {
            return *(current++);
        }
        return std::nullopt;
    }

    std::optional<std::string> ExpectConditionalOperator(std::vector<JDD::Lexer::Token>::iterator& current) {
        if (ExpectOperator(current, ">").has_value()) {
            if (ExpectOperator(current, "=").has_value()) {
                return ">=";
            }
            return ">";
        } else if (ExpectOperator(current, "<").has_value()) {
            if (ExpectOperator(current, "=").has_value()) {
                return "<=";
            }
            return "<";
        } else if (ExpectOperator(current, "=").has_value() && ExpectOperator(current, "=").has_value()) {
            return "==";
        } else if (ExpectOperator( current, "!").has_value() && ExpectOperator(current, "=").has_value()) {
            return "!=";
        }
        return std::nullopt;
    }
}