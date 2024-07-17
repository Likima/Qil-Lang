#include "interpreter.hpp"
#include <iostream>

void Interpreter::Advance() {
    // Implementation if needed
    return;
}

std::variant<int, float> Interpreter::Interpret(std::shared_ptr<GenericNode> current_node) const {
    if (!current_node) current_node = this->ast;
    if (!current_node) return 0;
    const std::string& text = current_node->getToken().text;
    const std::string& type = current_node->getToken().type_string;

    if(type == "number" || type == "float") {
        if(current_node->getToken().type == TT_INT) {
            return std::stoi(text);
        } else if (current_node->getToken().type == TT_FLOAT) {
            return std::stof(text);
        }
    } else if (type == "operator") {
        auto binaryNode = std::dynamic_pointer_cast<BinOpNode>(current_node);
        if (!binaryNode) {
            // Handle error: current_node is not a BinaryNode
            return -1;
        }

        auto left = Interpret(binaryNode->getLeftNode());
        auto right = Interpret(binaryNode->getRightNode());

        if (left.index() != right.index()) {
            // Placeholder error return; throw an exception or handle error properly
            return -1;
        }

        switch(current_node->getToken().type) {
            case TT_ADD:
                if (std::holds_alternative<int>(left))
                    return std::get<int>(left) + std::get<int>(right);
                else
                    return std::get<float>(left) + std::get<float>(right);
            case TT_MUL:
                if (std::holds_alternative<int>(left))
                    return std::get<int>(left) * std::get<int>(right);
                else
                    return std::get<float>(left) * std::get<float>(right);
            case TT_SUB:
                if (std::holds_alternative<int>(left))
                    return std::get<int>(left) - std::get<int>(right);
                else
                    return std::get<float>(left) - std::get<float>(right);
            case TT_DIV:
                if (std::holds_alternative<int>(left))
                    return std::get<int>(left) / std::get<int>(right);
                else
                    return std::get<float>(left) / std::get<float>(right);
            default:
                // Placeholder error return; throw an exception or handle error properly
                return -1;
        }
    }
    // Placeholder error return; throw an exception or handle error properly
    return 0;
}