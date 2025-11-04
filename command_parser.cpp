#include "command_parser.h"
#include <sstream>
#include <iostream>

void CommandParser::parse(const std::string& command) {
    params.clear();
    std::istringstream iss(command);
    std::string token;

    std::string current_key;
    std::string current_value;

    while (iss >> token) {
        if (token[0] == '-' && token.length() > 1) {
            // This is a key
            if (!current_key.empty()) {
                // Store the previous key-value pair
                params[current_key] = current_value;
            }
            current_key = token.substr(1); // Remove the '-'
            current_value.clear();
        } else if (!current_key.empty()) {
            // This is a value
            if (!current_value.empty()) {
                current_value += " ";
            }
            current_value += token;
        }
    }

    // Store the last key-value pair
    if (!current_key.empty()) {
        params[current_key] = current_value;
    }
}

std::string CommandParser::get_param(const std::string& key) const {
    auto it = params.find(key);
    if (it != params.end()) {
        return it->second;
    }
    return "";
}

bool CommandParser::has_param(const std::string& key) const {
    return params.find(key) != params.end();
}

void CommandParser::clear() {
    params.clear();
}