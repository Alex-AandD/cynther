#pragma once
#include <frontend/token.hpp>
#include <vector>
#include <string>

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
public:
    Lexer(std::string input);
    ~Lexer();

    std::vector<Token> scan_tokens();
    void push_token(Token);
    
    bool match(char c);
    char peek_next();
    bool at_end();

    Token push_simple_token(TOKENTYPE);
    Token push_int_token();
    Token push_double_token();
    Token push_string_token();
    Token push_comment_token();
};
