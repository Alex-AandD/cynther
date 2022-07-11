#pragma once
#include "frontend/scope.hpp"
#include "frontend/expression.hpp"
#include <vector>

class LLParser {
    private:
	std::vector<Token> tokens;
	size_t current;
	int parser_errors;
    public:
	LLParser(std::vector<Token> _tokens);
	~LLParser();

	Expr* parse();

	Expr* assignment();
	Expr* expression();
	Expr* term();
	Expr* factor();
	Expr* unary();
	Expr* primary();
	
	inline void advance(){ current++; }
	inline Token current_token(){ return tokens[current]; }
	inline TOKENTYPE get_token_type(size_t current_pos) {
	    return tokens[current_pos].get_type(); }
	inline bool at_end(){ return current > tokens.size(); }
	inline TOKENTYPE peek_next(){ 
	    return get_token_type(current+1);
	}
	bool match(std::vector<TOKENTYPE>); 
	void consume(TOKENTYPE, std::string error_message, Token token);
};
