#pragma once
#include "frontend/token.hpp"
#include <vector>

class Expr;

class Stmt {
    public:
	Stmt();
	virtual ~Stmt();
	[[nodiscard]] virtual std::string to_string() const noexcept = 0;
};

class WhileStmt: public Stmt {
    private:
	Expr* condition;
	Stmt* body;
    public:
	WhileStmt(Expr* condition, Stmt* body);
	~WhileStmt() override;

	[[nodiscard]] inline Expr* get_condition() const noexcept { return condition; };
	[[nodiscard]] inline Stmt* get_body() const noexcept { return body; };
	[[nodiscard]] std::string to_string() const noexcept override;
};

class IfStmt : public Stmt {
    private:
	Expr* condition;
	Stmt* body;
    public:
	IfStmt(Expr* condition, Stmt* body);
	~IfStmt() override;

	[[nodiscard]] inline Expr* get_condition() const noexcept { return condition; };
	[[nodiscard]] inline Stmt* get_body() const noexcept { return body; };
	[[nodiscard]] std::string to_string() const noexcept override;
};

class BlockStmt : public Stmt {
    private:
	std::vector<Stmt*> stmts;
    public:
	explicit BlockStmt(std::vector<Stmt*>);
	~BlockStmt() override;

	[[nodiscard]] inline std::vector<Stmt*> get_stmts() const noexcept { return stmts; }
	[[nodiscard]] std::string to_string() const noexcept override;
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
