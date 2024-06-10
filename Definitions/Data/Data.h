#pragma once

#include <iostream>
#include <map>
#include <optional>
#include "../Variable/Variable.h"

namespace JDD::Definitions {
    class Data {
    public:
        std::map<std::string, Variable> Variables;

        [[nodiscard]] bool isVariable(const std::string& name) const;
        std::optional<Variable> getVariableFromName(const std::string& name);
        void addVariableToData(const Variable& var);
        void addVariableToData(const std::string& name, const Value& value, const Types& type, const bool& isFinal);
        void removeVariableFromName(const std::string& name);
        void updateVariableValueFromData(const std::string& name, const std::string& value);
    };
}