#include "Data.h"

namespace JDD::Definitions {
    bool Data::isVariable(const std::string &name) const {
        if (Variables.contains(name)) {
            return true;
        }
        return false;
    }

    std::optional<Variable> Data::getVariableFromName(const std::string &name) {
        if (this->isVariable(name)) {
            return this->Variables[name];
        }
        return std::nullopt;
    }

    void Data::addVariableToData(const Variable &var) {
        if (!isVariable(var.name)) {
            this->Variables[var.name] = var;
        }
    }

    void Data::addVariableToData(const std::string& name, const Value& value, const Types& type, const bool& isFinal) {
        if (!isVariable(name)) {
            this->Variables[name] = Variable(name, value, type, isFinal);
        }
    }

    void Data::removeVariableFromName(const std::string &name) {
        if (this->isVariable(name)) {
            this->Variables.erase(name);
        }
    }

    void Data::updateVariableValueFromData(const std::string &name, const std::string &value) {
        this->Variables[name].value.content = value;
    }
}