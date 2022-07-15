#include "frontend/stmt.hpp"
#include "frontend/expression.hpp"

Stmt::Stmt(){ }
Stmt::~Stmt() { }

FunctionStmt::FunctionStmt(){}
FunctionStmt::FunctionStmt(std::vector<Expr*> ar, Stmt* bod):args(ar), body(bod) {};
FunctionStmt::~FunctionStmt(){
    if (body != nullptr){
	delete body;
	body = nullptr;
    }
}

std::string FunctionStmt::to_string() const noexcept {
    std::string func = "fun "; 
    for (auto& expr: args){
	if (expr != nullptr){
	    func += expr->to_string() + ",";
	}
    }
    func += body->to_string();
    return func;
}

ReturnStmt::ReturnStmt(Expr* val):value(val){}
ReturnStmt::~ReturnStmt(){
    if (value != nullptr){
	delete value;
	value = nullptr;
    }
}

std::string ReturnStmt::to_string() const noexcept {
    return "return"  " " + value->to_string();
}

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
	if (stmt != nullptr){
	    block_string +=  "\n	";
	    block_string += stmt->to_string();
	}
    }
    block_string += "\n}";
    return block_string;
}

AssignmentStmt::AssignmentStmt(Expr* ex, Expr* e): id_expr(ex), expression(e){ } 
AssignmentStmt::~AssignmentStmt(){
    if (id_expr != nullptr){
	delete id_expr;
	id_expr = nullptr;
    }

    if (expression != nullptr) {
	delete expression;
	expression = nullptr;
    }
}

std::string AssignmentStmt::to_string() const noexcept {
    return id_expr->to_string() + expression -> to_string();
}

IntDeclarationStmt::IntDeclarationStmt(Expr* _id, Expr* _expr)
    :id_expr(_id), value_expr(_expr) { }

IntDeclarationStmt::~IntDeclarationStmt(){
    if (id_expr != nullptr){
	delete id_expr;
	id_expr = nullptr;
    }

    if (value_expr != nullptr){
	delete value_expr;
	value_expr = nullptr;
    }
}

BoolDeclarationStmt::BoolDeclarationStmt(Expr* _id , Expr* _expr)
    :id_expr(_id), value_expr(_expr) { }
    
BoolDeclarationStmt::~BoolDeclarationStmt(){
    if (id_expr != nullptr){
	delete id_expr;
	id_expr = nullptr;
    }
    if(value_expr != nullptr){
	delete value_expr;
	value_expr = nullptr;
    }
}

StringDeclarationStmt::StringDeclarationStmt(Expr* _id, Expr* _expr)
    :id_expr(_id), value_expr(_expr) { }

StringDeclarationStmt::~StringDeclarationStmt(){
    if (id_expr != nullptr){
	delete id_expr;
	id_expr = nullptr;
    }

    if (value_expr != nullptr){
	delete value_expr;
	value_expr = nullptr;
    }
}

DoubleDeclarationStmt::DoubleDeclarationStmt(Expr* _id, Expr* _expr)
    :id_expr(_id), value_expr(_expr) { }

DoubleDeclarationStmt::~DoubleDeclarationStmt(){
    if (id_expr != nullptr){
	delete id_expr;
	id_expr = nullptr;
    }
	
    if (value_expr != nullptr){
	delete value_expr;
	value_expr = nullptr;
    }
}

std::string IntDeclarationStmt::to_string() const noexcept{
    return "int" " " + id_expr->to_string() + " "  "="  " " + value_expr->to_string();
}

std::string BoolDeclarationStmt::to_string() const noexcept{
    return "bool" " " + id_expr->to_string() + " "  "="  " " + value_expr->to_string();
}

std::string StringDeclarationStmt::to_string() const noexcept{
    return "string" " " + id_expr->to_string() + " "  "="  " " + value_expr->to_string();
}

std::string DoubleDeclarationStmt::to_string() const noexcept{
    return "double" " " + id_expr->to_string() + " "  "="  " " + value_expr->to_string();
}

CallStmt::CallStmt(Expr* expr): call_expr(expr){ }
CallStmt::~CallStmt(){
    if(call_expr != nullptr){
	delete call_expr;
	call_expr = nullptr;
    }
}

std::string CallStmt::to_string() const noexcept {
    return call_expr->to_string();
}

ExprStmt::ExprStmt(Expr* _id): id_expr(_id) { }
ExprStmt::~ExprStmt(){
    if(id_expr != nullptr){
	delete id_expr;
	id_expr = nullptr;
    }
}

std::string ExprStmt::to_string() const noexcept {
    return id_expr->to_string();
}


BoolListStmt::BoolListStmt(Expr* id, Expr* num, Expr* list_expr)
    : id_expr(id), num_values(num), values(list_expr){ }

BoolListStmt::~BoolListStmt(){
    if (id_expr != nullptr){
	delete id_expr;
	id_expr = nullptr;
    }

    if (num_values!= nullptr){
	delete num_values;
	num_values = nullptr;
    }

    if (values != nullptr){
	delete values;
	values = nullptr;
    }
}

std::string BoolListStmt::to_string() const noexcept {
    return "bool" "[" + num_values->to_string() + "]" " = " + values->to_string();
}
IntListStmt::IntListStmt(Expr* id, Expr* num, Expr* list_expr)
    : id_expr(id), num_values(num), values(list_expr){ }

IntListStmt::~IntListStmt(){
    if (id_expr != nullptr){
	delete id_expr;
	id_expr = nullptr;
    }

    if (num_values!= nullptr){
	delete num_values;
	num_values = nullptr;
    }

    if (values != nullptr){
	delete values;
	values = nullptr;
    }
}

std::string IntListStmt::to_string() const noexcept {
    return "int" "[" + num_values->to_string() + "]" " = " + values->to_string();
}
DoubleListStmt::DoubleListStmt(Expr* id, Expr* num, Expr* list_expr)
    : id_expr(id), num_values(num), values(list_expr){ }

DoubleListStmt::~DoubleListStmt(){
    if (id_expr != nullptr){
	delete id_expr;
	id_expr = nullptr;
    }

    if (num_values!= nullptr){
	delete num_values;
	num_values = nullptr;
    }

    if (values != nullptr){
	delete values;
	values = nullptr;
    }
}

std::string DoubleListStmt::to_string() const noexcept {
    return "double" "[" + num_values->to_string() + "]" " = " + values->to_string();
}
StringListStmt::StringListStmt(Expr* id, Expr* num, Expr* list_expr)
    : id_expr(id), num_values(num), values(list_expr){ }

StringListStmt::~StringListStmt(){
    if (id_expr != nullptr){
	delete id_expr;
	id_expr = nullptr;
    }

    if (num_values!= nullptr){
	delete num_values;
	num_values = nullptr;
    }

    if (values != nullptr){
	delete values;
	values = nullptr;
    }
}

std::string StringListStmt::to_string() const noexcept {
    return "string" "[" + num_values->to_string() + "]" " = " + values->to_string();
}
