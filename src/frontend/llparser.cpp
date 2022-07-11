#include "frontend/llparser.hpp"
#include "frontend/exceptions.hpp"

LLParser::LLParser(std::vector<Token> _tokens):
    tokens(_tokens), current(0) {} 
LLParser::~LLParser(){  }

Expr* LLParser::parse(){
    try {
	return expression();
    } catch(ParserError& err){
	std::cout << "error found: implement ParserError" << '\n';
    }
}

Expr* LLParser::expression(){
    return term();
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
