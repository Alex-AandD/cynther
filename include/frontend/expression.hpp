#pragma once
#include "frontend/token.hpp"
#include <string>

class Expr {
    public:
	Expr();
	virtual ~Expr() = 0;
	[[nodiscard]] std::string virtual to_string() const = 0;
};

class BinaryExpr : public Expr {
    private:
	Expr* left;
	Expr* right;
	Token op;
    public:
	explicit BinaryExpr(Token t, Expr* left, Expr* right); 

	BinaryExpr(BinaryExpr&&);
	BinaryExpr& operator=(BinaryExpr&&);

	~BinaryExpr() override;	

	[[nodiscard]] inline Expr* get_left() const noexcept { return left; }
	[[nodiscard]] inline Expr* get_right() const noexcept { return right; }
	[[nodiscard]] inline Token get_op() const noexcept { return op; }
	[[nodiscard]] std::string to_string() const noexcept override;
};

class UnaryExpr : public Expr {
    private: 
	Expr* right;
	Token op;
    public:
	explicit UnaryExpr(Token t, Expr* _right);
	~UnaryExpr() override;
    
	UnaryExpr(UnaryExpr&& other);
	UnaryExpr& operator=(UnaryExpr&& other);
	
	[[nodiscard]] inline Expr* get_right() const { return right; }
	[[nodiscard]] inline Token get_op() const { return op; }
	[[nodiscard]] std::string to_string() const override;
};

class IntExpr : public Expr {
    private:
	Token token; 
    public:
	explicit IntExpr(Token _token);
	~IntExpr() override;	
	[[nodiscard]] inline Token get_token() const noexcept { return token; }
	[[nodiscard]] inline std::string to_string() const noexcept override { return token.get_lexeme(); } 
};

class DoubleExpr : public Expr {
    private:
	Token token; 
    public:
	explicit DoubleExpr(Token _token);
	~DoubleExpr() override;	
    
	[[nodiscard]] inline Token get_token() const noexcept { return token; }
	[[nodiscard]] inline std::string to_string() const noexcept override { return token.get_lexeme(); } 
};

class StringExpr : public Expr {
    private:
	Token token; 
    public:
	explicit StringExpr(Token _token);
	~StringExpr() override;	
	
	[[nodiscard]] inline Token get_token() const noexcept{ return token; }
	[[nodiscard]] inline std::string to_string() const noexcept override {return token.get_lexeme(); } 
};

class BoolExpr : public Expr {
    private:
	Token token; 
    public:
	explicit BoolExpr(Token _token);
	~BoolExpr() override;	
	
	inline Token get_token() const { return token; }
	inline std::string to_string() const override { return token.get_lexeme(); }
};

class IdExpr : public Expr {
    private:
	Token token;
    public:
	explicit IdExpr(Token _token);
	~IdExpr() override;
	inline Token get_token() const { return token; }
	inline std::string to_string() const override {
	    return token.get_lexeme();
	}
};

class GroupingExpr : public Expr {
    private:
	Expr* expr;
    public:
	explicit GroupingExpr(Expr* _expr);
	~GroupingExpr();
	inline Expr* get_expr(){ return expr; }
	std::string to_string() const override {
	    return expr -> to_string();
	} 
};
