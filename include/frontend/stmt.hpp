#pragma once
#include "frontend/token.hpp"

class Expr;

class Stmt {
    public:
	Stmt();
	virtual ~Stmt();
	[[nodiscard]] virtual std::string to_string() const noexcept = 0;
};

class IntDeclarationStmt : public Stmt {
    private:
	Token id_token;
	Expr* expr;	
    public:
	IntDeclarationStmt(Token, Expr*);
	~IntDeclarationStmt() override;	

	[[nodiscard]] inline Token get_token() const noexcept { return id_token; }
	[[nodiscard]] inline Expr* get_expr() const noexcept { return expr; }
	[[nodiscard]] std::string to_string() const noexcept override;
};

class BoolDeclarationStmt: public Stmt {
    private:
	Token id_token;
	Expr* expr;
    public:
	BoolDeclarationStmt(Token, Expr*);
	~BoolDeclarationStmt() override;

	[[nodiscard]] inline Token get_token() const noexcept { return id_token; }
	[[nodiscard]] inline Expr* get_expr() const noexcept { return expr; }
	[[nodiscard]] std::string to_string() const noexcept override;
};

class DoubleDeclarationStmt: public Stmt {
    private:
	Token id_token;
	Expr* expr;
    public:
	DoubleDeclarationStmt(Token token, Expr*);
	~DoubleDeclarationStmt() override;

	[[nodiscard]] inline Token get_token() const noexcept { return id_token; }
	[[nodiscard]] inline Expr* get_expr() const noexcept { return expr; }
	[[nodiscard]] std::string to_string() const noexcept override;
};

class StringDeclarationStmt: public Stmt {
    private:
	Token id_token;
	Expr* expr;
    public:
	StringDeclarationStmt(Token, Expr*);
	~StringDeclarationStmt() override;

	[[nodiscard]] inline Token get_token() const noexcept { return id_token; }
	[[nodiscard]] inline Expr* get_expr() const noexcept { return expr; }
	[[nodiscard]] std::string to_string() const noexcept override;
};
