#pragma once
#include <stdexcept>
#include <string>

class UndefinedCharacter : std::exception {
    char char_wrong;
    size_t line;
    size_t offset;
public:
    UndefinedCharacter(char c, size_t line, size_t offset);
    void print_error();
};

class UndefinedLiteral : std::exception {
    std::string type;
    std::string lexeme;
    size_t line;
    size_t offset;
    
public:
    UndefinedLiteral(std::string type, std::string lex, 
	    size_t line, size_t offset);
    void print_error();
};

class MissingClosingQuote: std::exception {
    size_t line;
    size_t offset;
    
public:
    MissingClosingQuote(size_t line, size_t offset);
    void print_error();
};
