#pragma once
#include <stdexcept>

class UndefinedCharacter : std::exception {
    char char_wrong;
    size_t line;
    size_t offset;
public:
    UndefinedCharacter(char c, size_t line, size_t offset);
    void print_error();
};
