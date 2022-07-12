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
    int lexer_errors;
    static std::unordered_map<std::string, TOKENTYPE> keyword_map;

public:
    Lexer();
    Lexer(std::string input);
    ~Lexer();

    void set_input_string(std::string new_input){
	input_string = new_input;  }

    std::vector<Token> scan_tokens();
    
    [[nodiscard]] bool match(char c);
    char peek_next();
    [[nodiscard]] bool at_end() const noexcept;

    std::vector<TOKENTYPE> get_types() const;
    std::vector<std::string> get_lexemes() const;

    void push_simple_token(TOKENTYPE);
    void push_number_token();
    void push_int_token();
    void push_double_token();
    void push_string_token();
    void push_id_token();
    void push_comment_token();

    void tokens_to_string();
};
