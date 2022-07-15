#pragma once
#include "frontend/token.hpp"
#include <vector>

class Expr;
class Stmt;
class FunctionStmt;

class LLParser {
    private:
	std::vector<Token> tokens;
	std::vector<Stmt*> stmts;
	Token error_token;
	size_t current;
	int parser_errors;
    public:
	LLParser(std::vector<Token> _tokens);
	~LLParser();

	void synchronise(TOKENTYPE);
	void panic_mode(Token err, TOKENTYPE sync_point) noexcept;
	void panic_mode(TOKENTYPE sync_point) noexcept;

	inline void advance() noexcept { current++; }

	inline void set_error(Token tok) noexcept { error_token = tok; }
	inline void set_error() noexcept { error_token = previous_token(); }
	inline void inc_errors() noexcept { parser_errors++; }

	[[nodiscard]] inline int line_error() const noexcept { return error_token.get_line(); }
	[[nodiscard]] inline int line_error(Token tok) const noexcept { return tok.get_line(); }
	[[nodiscard]] inline int column_error() const noexcept { return error_token.get_offset(); }
	[[nodiscard]] inline int column_error(Token tok) const noexcept { return tok.get_offset(); }
	
	void program();
	[[nodiscard]] std::vector<Stmt*> parse();
	[[nodiscard]] Stmt* declaration();    
	[[nodiscard]] Stmt* int_declaration();
	[[nodiscard]] Stmt* string_declaration();
	[[nodiscard]] Stmt* bool_declaration();
	[[nodiscard]] Stmt* double_declaration();

	[[nodiscard]] Stmt* int_list_declaration();
	[[nodiscard]] Stmt* string_list_declaration();
	[[nodiscard]] Stmt* bool_list_declaration();
	[[nodiscard]] Stmt* double_list_declaration();

	[[nodiscard]] Stmt* statement();
	[[nodiscard]] Stmt* return_statement();
	[[nodiscard]] Stmt* fun_statement();
	[[nodiscard]] Stmt* while_statement();
	[[nodiscard]] Stmt* if_statement();
	[[nodiscard]] Stmt* block();
	[[nodiscard]] Stmt* assignment_statement();
	[[nodiscard]] Stmt* call_stmt();
	[[nodiscard]] Stmt* expr_stmt();

	[[nodiscard]] Expr* expression();
	[[nodiscard]] Expr* assignment();
	[[nodiscard]] Expr* comparison();	
	[[nodiscard]] Expr* equality();	
	[[nodiscard]] Expr* and_expr();
	[[nodiscard]] Expr* or_expr();
	[[nodiscard]] Expr* term();
	[[nodiscard]] Expr* factor();
	[[nodiscard]] Expr* unary();
	[[nodiscard]] Expr* primary();
	[[nodiscard]] Expr* call_expr();
	
	void fun_args(FunctionStmt*); 
	[[nodiscard]] TOKENTYPE resolve_type();
	[[nodiscard]] inline Token current_token() const noexcept { return tokens[current]; }
	[[nodiscard]] inline Token previous_token() const noexcept { return tokens[current - 1]; }
	[[nodiscard]] inline TOKENTYPE get_token_type(size_t current_pos) const noexcept
				       { return tokens[current_pos].get_type(); }
	[[nodiscard]] inline bool at_end() const noexcept { return current >= tokens.size(); }
	[[nodiscard]] inline TOKENTYPE peek_next() const noexcept { return get_token_type(current+1);}
	[[nodiscard]] bool match(std::vector<TOKENTYPE>) const noexcept; 
	[[nodiscard]] bool match(TOKENTYPE) const noexcept;
	[[nodiscard]] std::string tree_to_string() const noexcept;
};
