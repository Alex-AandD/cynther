#pragma once
#include "frontend/token.hpp"
#include <vector>
#include <string>
#include <unordered_map>

class Lexer {
    /* current -> points to the current character examined
     * start   -> used for bigger literals (ints, strings, keywords ...)
     * tokens  -> list of tokens encapsulating info
     */
private:
    size_t current;
    size_t start;
    size_t line;
    std::vector<Token> tokens;
    std::string input_string;
    static std::unordered_map<std::string, TOKENTYPE> keyword_map;

public:
    Lexer(std::string input);
    ~Lexer();

    std::vector<Token> scan_tokens();
    void push_token(Token);
    
    bool match(char c);
    char peek_next();
    bool at_end();

    void push_simple_token(TOKENTYPE);
    void push_number_token();
    void push_int_token();
    void push_double_token();
    void push_string_token();
    void push_id_token();
    void push_comment_token();

    void __repr__();
};
