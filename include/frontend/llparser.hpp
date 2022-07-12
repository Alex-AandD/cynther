#pragma once
#include "frontend/token.hpp"
#include <vector>

class Expr;
class Stmt;

class LLParser {
    private:
	std::vector<Token> tokens;
	size_t current;
	int parser_errors;
	std::vector<Stmt*> stmts;
    public:
	LLParser(std::vector<Token> _tokens);
	~LLParser();

	std::vector<Stmt*> parse();
	void synchronise(TOKENTYPE);
	
	void program();
	Stmt* declaration();    
	Stmt* int_declaration();
	Stmt* string_declaration();
	Stmt* bool_declaration();
	Stmt* double_declaration();
	
	Expr* expression();
	Expr* and_expr();
	Expr* or_expr();
	Expr* term();
	Expr* factor();
	Expr* unary();
	Expr* primary();
	
	inline void advance(){ current++; }
	[[nodiscard]] inline Token current_token(){ return tokens[current]; }
	[[nodiscard]] inline Token previous_token() { return tokens[current - 1]; }
	[[nodiscard]] inline TOKENTYPE get_token_type(size_t current_pos) {
	    return tokens[current_pos].get_type(); }
	[[nodiscard]] inline bool at_end(){ return current >= tokens.size(); }
	[[nodiscard]] inline TOKENTYPE peek_next() { 
	    return get_token_type(current+1);
	}
	[[nodiscard]] bool match(std::vector<TOKENTYPE>); 
	void consume(TOKENTYPE, std::string error_message, Token token);

	[[nodiscard]] std::string tree_to_string() const noexcept;
};
