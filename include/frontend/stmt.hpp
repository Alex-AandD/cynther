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
	std::vector<Expr*> args;
	std::vector<TOKENTYPE> types;
	Stmt* body;
	TOKENTYPE return_type;
    public:
	FunctionStmt();
	FunctionStmt(std::vector<Expr*>, Stmt*);
	~FunctionStmt() override;

	[[nodiscard]] inline std::vector<Expr*> get_args() const noexcept { return args; }
	[[nodiscard]] inline std::vector<TOKENTYPE> get_types() const noexcept { return types; }
	[[nodiscard]] inline Stmt* get_body() const noexcept { return body; }
	[[nodiscard]] inline TOKENTYPE get_return_type() const noexcept { return return_type; }
	[[nodiscard]] std::string to_string() const noexcept override;

	inline void push_arg (Expr* expr) noexcept { args.push_back(expr); }
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
	Expr* id_expr;
	Expr* expression;
    public:
	explicit AssignmentStmt(Expr*, Expr*);
	~AssignmentStmt() override;
	[[nodiscard]] Expr* get_expression() const noexcept { return expression; }
	[[nodiscard]] Expr* get_id() const noexcept { return id_expr; }
	[[nodiscard]] std::string to_string() const noexcept override;
};

class IntDeclarationStmt : public Stmt {
    private:
	Expr* id_expr;
	Expr* value_expr;	
    public:
	explicit IntDeclarationStmt(Expr*, Expr*);
	~IntDeclarationStmt() override;	

	[[nodiscard]] inline Expr* get_id_expr() const noexcept { return id_expr; }
	[[nodiscard]] inline Expr* get_value_expr() const noexcept { return value_expr; }
	[[nodiscard]] std::string to_string() const noexcept override;
};

class BoolDeclarationStmt: public Stmt {
    private:
	Expr* id_expr;
	Expr* value_expr;
    public:
	explicit BoolDeclarationStmt(Expr*, Expr*);
	~BoolDeclarationStmt() override;

	[[nodiscard]] inline Expr* get_id_expr() const noexcept { return id_expr; }
	[[nodiscard]] inline Expr* get_value_expr() const noexcept { return value_expr; }
	[[nodiscard]] std::string to_string() const noexcept override;
};

class DoubleDeclarationStmt: public Stmt {
    private:
	Expr* id_expr;
	Expr* value_expr;
    public:
	explicit DoubleDeclarationStmt(Expr*, Expr*);
	~DoubleDeclarationStmt() override;

	[[nodiscard]] inline Expr* get_id_expr() const noexcept { return id_expr; }
	[[nodiscard]] inline Expr* get_value_expr() const noexcept { return value_expr; }
	[[nodiscard]] std::string to_string() const noexcept override;
};

class StringDeclarationStmt: public Stmt {
    private:
	Expr* id_expr;
	Expr* value_expr;
    public:
	explicit StringDeclarationStmt(Expr*, Expr*);
	~StringDeclarationStmt() override;

	[[nodiscard]] inline Expr* get_id_expr() const noexcept { return id_expr; }
	[[nodiscard]] inline Expr* get_value_expr() const noexcept { return value_expr; }
	[[nodiscard]] std::string to_string() const noexcept override;
};

class IntListStmt: public Stmt {
    private:
	Expr* id_expr;
	Expr* num_values;
	Expr* values;  // ListExpr
    public:
	explicit IntListStmt(Expr*, Expr*, Expr*);
	~IntListStmt() override;	

	[[nodiscard]] inline Expr* get_id_expr() const noexcept { return id_expr; }
	[[nodiscard]] inline Expr* get_num_values() const noexcept { return num_values; }
	[[nodiscard]] inline Expr* get_values() const noexcept { return values; }
	[[nodiscard]] std::string to_string() const noexcept override;
};

class StringListStmt: public Stmt {
    private:
	Expr* id_expr;
	Expr* num_values;
	Expr* values;  // ListExpr	
    public:
	explicit StringListStmt(Expr*, Expr*, Expr*);
	~StringListStmt() override;	

	[[nodiscard]] inline Expr* get_id_expr() const noexcept { return id_expr; }
	[[nodiscard]] inline Expr* get_num_values() const noexcept { return num_values; }
	[[nodiscard]] inline Expr* get_values() const noexcept { return values; }
	[[nodiscard]] std::string to_string() const noexcept override;
};

class DoubleListStmt: public Stmt {
    private:
	Expr* id_expr;
	Expr* num_values;
	Expr* values;  // ListExpr	
    public:
	explicit DoubleListStmt(Expr*, Expr*, Expr*);
	~DoubleListStmt() override;	

	[[nodiscard]] inline Expr* get_id_expr() const noexcept { return id_expr; }
	[[nodiscard]] inline Expr* get_num_values() const noexcept { return num_values; }
	[[nodiscard]] inline Expr* get_values() const noexcept { return values; }
	[[nodiscard]] std::string to_string() const noexcept override;
};

class BoolListStmt: public Stmt {
    private:
	Expr* id_expr;
	Expr* num_values;
	Expr* values;  // ListExpr	
    public:
	explicit BoolListStmt(Expr*, Expr*, Expr*);
	~BoolListStmt() override;	

	[[nodiscard]] inline Expr* get_id_expr() const noexcept { return id_expr; }
	[[nodiscard]] inline Expr* get_num_values() const noexcept { return num_values; }
	[[nodiscard]] inline Expr* get_values() const noexcept { return values; }
	[[nodiscard]] std::string to_string() const noexcept override;
};

class CallStmt: public Stmt {
    private:
	Expr* call_expr;	
    public:
	explicit CallStmt(Expr*);
	~CallStmt() override;
	[[nodiscard]] inline Expr* get_call_expr() const noexcept { return call_expr; }
	[[nodiscard]] std::string to_string() const noexcept override;
};

class ExprStmt: public Stmt {
    private:
	Expr* id_expr;
    public:
	explicit ExprStmt(Expr*);
	~ExprStmt() override;
	[[nodiscard]] inline Expr* get_id_expr() const noexcept { return id_expr; }
	[[nodiscard]] std::string to_string() const noexcept override;
};
