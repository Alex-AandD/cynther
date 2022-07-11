#pragma once
#include "frontend/token.hpp"
#include <string>

class Expr {
    public:
	Expr();
	virtual ~Expr() = 0;
	std::string virtual to_string() const = 0;
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

	inline Expr* get_left() const { return left; }
	inline Expr* get_right() const { return right; }
	inline Token get_op() const { return op; }

	std::string to_string() const override;
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
	
	inline Expr* get_right() const { return right; }
	inline Token get_op() const { return op; }
	std::string to_string() const override;
};

class IntExpr : public Expr {
    private:
	Token token; 
    public:
	explicit IntExpr(Token _token);
	~IntExpr() override;	
	inline Token get_token() { return token; }
	inline std::string to_string() const override { return token.get_lexeme(); } 
};

class DoubleExpr : public Expr {
    private:
	Token token; 
    public:
	explicit DoubleExpr(Token _token);
	~DoubleExpr() override;	
    
	inline Token get_token() { return token; }
	inline std::string to_string() const override { return token.get_lexeme(); } 
};

class StringExpr : public Expr {
    private:
	Token token; 
    public:
	explicit StringExpr(Token _token);
	~StringExpr() override;	
	
	inline Token get_token() const { return token; }
	inline std::string to_string() const override {return token.get_lexeme(); } 
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
