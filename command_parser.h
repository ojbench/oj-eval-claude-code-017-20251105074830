#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <string>
#include <map>

class CommandParser {
private:
    std::map<std::string, std::string> params;

public:
    void parse(const std::string& command);
    std::string get_param(const std::string& key) const;
    bool has_param(const std::string& key) const;
    void clear();
};

#endif