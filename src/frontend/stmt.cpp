#include "frontend/stmt.hpp"
#include "frontend/expression.hpp"

Stmt::Stmt(){ }
Stmt::~Stmt() { }

IntDeclarationStmt::IntDeclarationStmt(Token token, Expr* _expr)
    :id_token(token), expr(_expr) { }

IntDeclarationStmt::~IntDeclarationStmt(){
    if (expr != nullptr){
	delete expr;
    }
    expr = nullptr;
}

BoolDeclarationStmt::BoolDeclarationStmt(Token token, Expr* _expr)
    :id_token(token), expr(_expr) { }
    
BoolDeclarationStmt::~BoolDeclarationStmt(){
    if (expr != nullptr){
	delete expr;
    }
    expr = nullptr;
}

StringDeclarationStmt::StringDeclarationStmt(Token token, Expr* _expr)
    :id_token(token), expr(_expr) { }

StringDeclarationStmt::~StringDeclarationStmt(){
    if (expr != nullptr){
	delete expr;
    }
    expr = nullptr;
}

DoubleDeclarationStmt::DoubleDeclarationStmt(Token token, Expr* _expr)
    :id_token(token), expr(_expr) { }

DoubleDeclarationStmt::~DoubleDeclarationStmt(){
    if (expr != nullptr){
	delete expr;
    }
    expr = nullptr;
}

std::string IntDeclarationStmt::to_string() const noexcept{
    return "int" " " + id_token.get_lexeme() + " "  "="  " " + expr->to_string();
}

std::string BoolDeclarationStmt::to_string() const noexcept{
    return "bool" " " + id_token.get_lexeme() + " "  "="  " " + expr->to_string();
}

std::string StringDeclarationStmt::to_string() const noexcept{
    return "string" " " + id_token.get_lexeme() + " "  "="  " " + expr->to_string();
}

std::string DoubleDeclarationStmt::to_string() const noexcept{
    return "double" " " + id_token.get_lexeme() + " "  "="  " " + expr->to_string();
}
