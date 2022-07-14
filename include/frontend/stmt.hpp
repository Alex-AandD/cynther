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

class FunctionStmt: public Stmt{
    private:
	std::vector<Token> args;
	std::vector<TOKENTYPE> types;
	Stmt* body;
	TOKENTYPE return_type;
    public:
	FunctionStmt();
	FunctionStmt(std::vector<Token>, Stmt*);
	~FunctionStmt() override;

	[[nodiscard]] inline std::vector<Token> get_args() const noexcept { return args; }
	[[nodiscard]] inline std::vector<TOKENTYPE> get_types() const noexcept { return types; }
	[[nodiscard]] inline Stmt* get_body() const noexcept { return body; }
	[[nodiscard]] inline TOKENTYPE get_return_type() const noexcept { return return_type; }
	[[nodiscard]] std::string to_string() const noexcept override;

	inline void push_arg (Token token) noexcept { args.push_back(token); }
	inline void push_type (TOKENTYPE type) noexcept { types.push_back(type); }
	inline void set_body(Stmt* stmt_body) { body = stmt_body; }
	inline void set_return_type(TOKENTYPE type) noexcept { return_type= type; }
};

class ReturnStmt: public Stmt {
    private:
	Expr* value;	
    public:
	explicit ReturnStmt(Expr*);
	~ReturnStmt() override;
	[[nodiscard]] inline Expr* get_expr() const noexcept { return value; };
	[[nodiscard]] std::string to_string() const noexcept override;
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

class AssignmentStmt: public Stmt {
    private:
	Token id_token;
	Expr* expression;
    public:
	explicit AssignmentStmt(Token, Expr*);
	~AssignmentStmt() override;
	[[nodiscard]] Expr* get_expression() const noexcept { return expression; }
	[[nodiscard]] Token get_id() const noexcept { return id_token; }
	[[nodiscard]] std::string to_string() const noexcept override;
};

class IntDeclarationStmt : public Stmt {
    private:
	Token id_token;
	Expr* expr;	
    public:
	explicit IntDeclarationStmt(Token, Expr*);
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
	explicit BoolDeclarationStmt(Token, Expr*);
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
	explicit DoubleDeclarationStmt(Token token, Expr*);
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
	explicit StringDeclarationStmt(Token, Expr*);
	~StringDeclarationStmt() override;

	[[nodiscard]] inline Token get_token() const noexcept { return id_token; }
	[[nodiscard]] inline Expr* get_expr() const noexcept { return expr; }
	[[nodiscard]] std::string to_string() const noexcept override;
};
