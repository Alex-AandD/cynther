#include "frontend/stmt.hpp"
#include "frontend/expression.hpp"

Stmt::Stmt(){ }
Stmt::~Stmt() { }


WhileStmt::WhileStmt(Expr* cond, Stmt* bod):condition(cond), body(bod) { }
WhileStmt::~WhileStmt(){
    if (condition != nullptr){
	delete condition;
	condition = nullptr;
    }

    if (body != nullptr){
	delete body;
	body = nullptr;
    }
}

std::string WhileStmt::to_string() const noexcept {
    return "while" + condition->to_string() + " => " + body->to_string(); 
}

IfStmt::IfStmt(Expr* cond, Stmt* bod):condition(cond), body(bod) { }
IfStmt::~IfStmt(){
    if (condition != nullptr){
	delete condition;
	condition = nullptr;
    }

    if (body != nullptr){
	delete body;
	body = nullptr;
    }
}

std::string IfStmt::to_string() const noexcept {
    return "if" + condition->to_string() + " => " + body->to_string(); 
}

BlockStmt::BlockStmt(std::vector<Stmt*> _stmts):stmts(_stmts){}
BlockStmt::~BlockStmt(){
    for (auto& stmt: stmts){
	if (stmt != nullptr){
	    delete stmt;
	    stmt = nullptr;
	}
    }
}

std::string BlockStmt::to_string() const noexcept {
    std::string block_string = "{";
    for (auto& stmt: stmts){
	block_string +=  "\n	";
	block_string += stmt->to_string();
    }
    block_string += "\n}";
    return block_string;
}

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
