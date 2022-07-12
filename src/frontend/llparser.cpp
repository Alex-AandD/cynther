#include "frontend/llparser.hpp"
#include "frontend/exceptions.hpp"
#include "frontend/stmt.hpp"
#include "frontend/expression.hpp"

LLParser::LLParser(std::vector<Token> _tokens):
    tokens(_tokens), current(0) {} 
LLParser::~LLParser(){ 
    for (auto& stmt: stmts){
	delete stmt;
	stmt = nullptr;
    }
}

std::vector<Stmt*> LLParser::parse(){
    try {
	program();
    } catch(...){
	std::cout << "error found: implement ParserError" << '\n';
    }
    return stmts;
}

void LLParser::program(){
    while (!at_end()){
	Stmt* stmt = declaration();
	stmts.push_back(stmt);
    }
}

Stmt* LLParser::declaration(){
    if (match({INT_TYPE})){
	advance();
	return int_declaration();}

    if (match({STRING_TYPE})){
	advance();
	return string_declaration();}

    if (match({BOOL_TYPE})){
	advance();
	return bool_declaration();}

    if (match({DOUBLE_TYPE})){
	advance();
	return double_declaration();}

    return nullptr;
}

Stmt* LLParser::int_declaration(){
    if (match({ID})){
	Token id_token = current_token();
	advance();
	if (match({EQUAL})){
	    advance();
	    Expr* expr = expression();
	    if (match({SEMICOLON})){
		advance();
		return new IntDeclarationStmt(id_token, expr);
	    }
	    std::cout << "implement semicolon error msg" << '\n';
	} else {
	    std::cout << "Implement error msg" << '\n';
	}
    }
    return nullptr;
}

Stmt* LLParser::double_declaration(){
    if (match({ID})){
	Token id_token = current_token();
	advance();
	if (match({EQUAL})){
	    advance();
	    Expr* expr = expression();
	    if (match({SEMICOLON})){
		advance();
		return new DoubleDeclarationStmt(id_token, expr);
	    }
	    std::cout << "implement semicolon error msg" << '\n';
	} else {
	    std::cout << "Implement error msg" << '\n';
	}
    }
    return nullptr;
}

Stmt* LLParser::string_declaration(){
    if (match({ID})){
	Token id_token = current_token();
	advance();
	if (match({EQUAL})){
	    advance();
	    Expr* expr = expression();
	    if (match({SEMICOLON})){
		advance();
		return new StringDeclarationStmt(id_token, expr);
	    }
	    std::cout << "implement semicolon error msg" << '\n';

	} else {
	    std::cout << "Implement error msg" << '\n';
	}
    }
    return nullptr;
}

Stmt* LLParser::bool_declaration(){
    
    if (match({ID})){
	Token id_token = current_token();
	advance();
	if (match({EQUAL})){
	    advance();
	    Expr* expr = expression();
	    if (match({SEMICOLON})){
		advance();
		return new BoolDeclarationStmt(id_token, expr);
	    }
	    std::cout << "Implement semicolon error msg" << '\n';
	} else {
	    std::cout << "Implement error msg" << '\n';
	}
    }
    return nullptr;
}

Expr* LLParser::expression(){
    return or_expr();
}

Expr* LLParser::or_expr(){
    Expr* left = and_expr(); 
    while(match({OR})){
	Token op = current_token();
	advance();
	Expr* right = and_expr();	
	left = new BinaryExpr(op, left, right);
    }
    return left;
}

Expr* LLParser::and_expr(){
    Expr* left = term(); 
    while(match({AND})){
	Token op = current_token();
	advance();
	Expr* right = term();	
	left = new BinaryExpr(op, left, right);
    }
    return left;
}

Expr* LLParser::term(){
    Expr* left = factor();
    while(match({PLUS, MINUS})){
	Token op = current_token();	
	advance();
	Expr* right = factor(); 	
	left = new BinaryExpr(op, left, right);
    }
    return left;
}

Expr* LLParser::factor(){
    Expr* left = unary(); 
    while(match({TIMES, SLASH})){
	Token op = current_token();
	advance();
	Expr* right = unary();
	left = new BinaryExpr(op, left, right);
    }
    return left;
}

Expr* LLParser::unary(){
    if (match({NOT, MINUS})){
	Token op = current_token();
	advance();
	Expr* right = unary();
	return new UnaryExpr(op, right);
    }
    return primary();
}

Expr* LLParser::primary(){
    if (match({INT})) { 
	Expr* inty = new IntExpr(current_token());
	advance();
	return inty;
    }

    if (match({STRING})){
	Expr* stringy = new StringExpr(current_token());
	advance();
	return stringy;
    }

    if (match({DOUBLE})){
	Expr* doubly = new DoubleExpr(current_token());
	advance();
	return doubly;
    }
    
    if (match({ID})){
	Expr* idy = new IdExpr(current_token());
	advance();
	return idy;
    }

    // TODO: fix the consume function
    if (match({LEFT_PAR})){
	Token left_par = current_token(); 
	advance();
	Expr* _expr = expression();
	consume(RIGHT_PAR, "error: missing closing parenthesis: ", left_par);
	return new GroupingExpr(_expr);
    }
    return nullptr;
}

void LLParser::consume(TOKENTYPE expected_type, std::string error_msg,
		Token bad_token){

    if (get_token_type(current) != expected_type){
	std::cerr << error_msg << bad_token.get_line() << ":" << bad_token.get_offset();	
	exit(0); 
    }
    advance();
}

bool LLParser::match(std::vector<TOKENTYPE> v){
    if (at_end()) return false;
    for (auto& type: v){
	if (type == get_token_type(current)){
	    return true;
	}
    }
    return false;
}

std::string LLParser::tree_to_string() const noexcept {
    std::string final_string;
    for (auto& stmt: stmts){
	final_string += stmt->to_string() + '\n';	
    }
    return final_string;
}
