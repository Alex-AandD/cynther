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

	[[nodiscard]] std::vector<Stmt*> parse();
	void synchronise(TOKENTYPE);
	
	void program();
	[[nodiscard]] Stmt* statement();
	[[nodiscard]] Stmt* if_statement();
	[[nodiscard]] Stmt* block();

	[[nodiscard]] Stmt* declaration();    
	[[nodiscard]] Stmt* int_declaration();
	[[nodiscard]] Stmt* string_declaration();
	[[nodiscard]] Stmt* bool_declaration();
	[[nodiscard]] Stmt* double_declaration();
	
	[[nodiscard]] Expr* expression();
	[[nodiscard]] Expr* and_expr();
	[[nodiscard]] Expr* or_expr();
	[[nodiscard]] Expr* term();
	[[nodiscard]] Expr* factor();
	[[nodiscard]] Expr* unary();
	[[nodiscard]] Expr* primary();
	
	inline void advance() noexcept { current++; }
	[[nodiscard]] inline Token current_token() const noexcept { return tokens[current]; }
	[[nodiscard]] inline Token previous_token() const noexcept { return tokens[current - 1]; }
	[[nodiscard]] inline TOKENTYPE get_token_type(size_t current_pos) const noexcept {
					return tokens[current_pos].get_type(); }
	[[nodiscard]] inline bool at_end() const noexcept { return current >= tokens.size(); }
	[[nodiscard]] inline TOKENTYPE peek_next() const noexcept { return get_token_type(current+1);}
	[[nodiscard]] bool match(std::vector<TOKENTYPE>) const noexcept; 
	[[nodiscard]] bool match(TOKENTYPE) const noexcept;
	[[nodiscard]] std::string tree_to_string() const noexcept;
};
