#include "frontend/expression.hpp"
#include <iostream>

Expr::Expr(){ }
Expr::~Expr() { }

BinaryExpr::BinaryExpr(Token _op, Expr* _left, Expr* _right)
    : left(_left), right(_right), op(_op) {};

BinaryExpr::~BinaryExpr(){
    if (left) delete left;
    if (right) delete right;
    right = left = nullptr;
}

BinaryExpr::BinaryExpr(BinaryExpr&& other){
    if(&other != this){	
	op = other.op;
	left = other.left;
	right = other.right;
	other.left = nullptr;
	other.right= nullptr;
    }
}

AssignmentExpr::AssignmentExpr(Token token, Expr* _expr)
    :id_token(token), expr(_expr) { }

AssignmentExpr::~AssignmentExpr(){
    if (expr != nullptr){
	delete expr;
    }
    expr = nullptr;
}

std::string AssignmentExpr::to_string() const noexcept {
    return id_token.get_lexeme() + " "  "="  " " + expr->to_string();
}

BinaryExpr& BinaryExpr::operator=(BinaryExpr&& other){
    if(&other != this){	
	delete left;
	delete right;

	op = other.op;
	left = other.left;
	right = other.right;

	other.left = nullptr;
	other.right= nullptr;
    }
    return *this;
}

std::string BinaryExpr::to_string() const noexcept{
    return "(" + left->to_string() + op.get_lexeme() + right->to_string() + ")"; 
}

UnaryExpr::UnaryExpr(Token _op, Expr* _right):right(_right), op(_op){}
UnaryExpr::UnaryExpr(UnaryExpr&& other){
    if (&other != this){
	op = other.op;
	right = other.right;
	other.right=nullptr;
    }
}

UnaryExpr& UnaryExpr::operator=(UnaryExpr&& other){
    if (&other != this){
	delete right;
	op = other.op;
	right = other.right;
	other.right = nullptr;
    }
    return *this;
}

UnaryExpr::~UnaryExpr(){
    if (right) delete right;
    right = nullptr;
}

std::string UnaryExpr::to_string() const {
    return "(" + op.get_lexeme() + right->to_string() + ")";    
}

IntExpr::IntExpr(Token _token): token(_token){}
IntExpr::~IntExpr(){ }

DoubleExpr::DoubleExpr(Token _token): token(_token){}
DoubleExpr::~DoubleExpr(){ }

StringExpr::StringExpr(Token _token): token(_token){}
StringExpr::~StringExpr(){ }

BoolExpr::BoolExpr(Token _token): token(_token){}
BoolExpr::~BoolExpr(){ }

IdExpr::IdExpr(Token _token): token(_token){}
IdExpr::~IdExpr(){ }

GroupingExpr::GroupingExpr(Expr* _expr): expr(_expr){}
GroupingExpr::~GroupingExpr(){
    if (expr) delete expr;
    expr = nullptr;
}
