#include "frontend/llparser.hpp"
#include "frontend/exceptions.hpp"
#include "frontend/stmt.hpp"
#include "frontend/expression.hpp"

LLParser::LLParser(std::vector<Token> _tokens): tokens(_tokens), current(0) {} 

LLParser::~LLParser(){ 
    for (auto& stmt: stmts){
	delete stmt;
	stmt = nullptr;
    }
}

std::vector<Stmt*> LLParser::parse(){
    program();
    return stmts;
}

void LLParser::program(){
    while (!at_end()){
	try {
	    Stmt* stmt = statement();
	    stmts.push_back(stmt);
	} catch(ParserError& err){
	    err.show_error();
	}
    }
}

Stmt* LLParser::statement(){
    if (match(IF)){
	return if_statement();
    }
    return block();
}

Stmt* LLParser::if_statement(){
    advance();
    Expr* condition = expression();
    Token token = current_token();
    if (match(ARROW)){
	advance();
	Stmt* body = block();
	return new IfStmt(condition, body);
    } else {
	parser_errors++;
	synchronise(RIGHT_BRACE);
	throw ParserError("expected arrow after condition", token.get_line(), token.get_offset());
    }
    return nullptr;
}


Stmt* LLParser::block(){
    if (match(LEFT_BRACE)){
	advance();
	std::vector<Stmt*> v_stmts;
	while(!match(RIGHT_BRACE)){
	    v_stmts.push_back(statement());
	}
	if (at_end()) {
	    throw ParserError("missing right brace", previous_token().get_line(), previous_token().get_offset());
	    exit(1);
	}
	advance();
	return new BlockStmt(v_stmts);
    }
    return declaration();
}

Stmt* LLParser::declaration(){
    if (match(INT_TYPE)){
	advance();
	return int_declaration();}

    if (match(STRING_TYPE)){
	advance();
	return string_declaration();}

    if (match(BOOL_TYPE)){
	advance();
	return bool_declaration();}

    if (match(DOUBLE_TYPE)){
	advance();
	return double_declaration();}

    return nullptr;
}

Stmt* LLParser::int_declaration(){
    Token id_token = current_token();
    if (match(ID)){
	advance();
	if (match(EQUAL)){
	    advance();
	    Expr* expr = expression();
	    if (match(SEMICOLON)){
		advance();
		return new IntDeclarationStmt(id_token, expr);
	    }
	    Token curr_token = previous_token();
	    synchronise(SEMICOLON);
	    throw ParserError("missing semicolon", curr_token.get_line(), curr_token.get_offset());
	} else {
	    synchronise(SEMICOLON);
	    throw ParserError("incomplete variable declaration missing '='",
		    id_token.get_line(), id_token.get_offset());
	}
    } else {
	    parser_errors++;
	    synchronise(SEMICOLON);
	    throw ParserError("expected id after type INT",
		    id_token.get_line(), id_token.get_offset());

    }
    return nullptr;
}

Stmt* LLParser::double_declaration(){
    Token id_token = current_token();
    if (match(ID)){
	advance();
	if (match(EQUAL)){
	    advance();
	    Expr* expr = expression();
	    if (match(SEMICOLON)){
		advance();
		return new DoubleDeclarationStmt(id_token, expr);
	    }
	    Token curr_token = previous_token();
	    parser_errors++;
	    synchronise(SEMICOLON);
	    throw ParserError("missing semicolon", curr_token.get_line(), curr_token.get_offset());
	} else {
	    parser_errors++;
	    synchronise(SEMICOLON);
	    throw ParserError("incomplete variable declaration, missing '='",
		    id_token.get_line(), id_token.get_offset());
	} 
    } else {
	synchronise(SEMICOLON);
	parser_errors++;
	throw ParserError("expected id after type DOUBLE", id_token.get_line(),
		id_token.get_offset());
    }
    return nullptr;
}

Stmt* LLParser::string_declaration(){
    Token id_token = current_token();
    if (match(ID)){
	advance();
	if (match(EQUAL)){
	    advance();
	    Expr* expr = expression();
	    if (match(SEMICOLON)){
		advance();
		return new StringDeclarationStmt(id_token, expr);
	    }
	    Token curr_token = previous_token();
	    parser_errors++;
	    synchronise(SEMICOLON);
	    throw ParserError("missing semicolon", curr_token.get_line(), curr_token.get_offset());
	} else {
	    synchronise(SEMICOLON);
	    parser_errors++;
	    throw ParserError("incomplete variable declaration missing '='",
		    id_token.get_line(), id_token.get_offset());
	}

    } else {
	synchronise(SEMICOLON);
	parser_errors++;
	throw ParserError("expected id after type STRING", id_token.get_line(),
		id_token.get_offset());
    }
    return nullptr;
}

Stmt* LLParser::bool_declaration(){
    Token id_token = current_token(); 
    if (match(ID)){
	advance();
	if (match(EQUAL)){
	    advance();
	    Expr* expr = expression();
	    if (match(SEMICOLON)){
		advance();
		return new BoolDeclarationStmt(id_token, expr);
	    }
	    Token curr_token = previous_token();
	    parser_errors++;
	    synchronise(SEMICOLON);
	    throw ParserError("missing semicolon", curr_token.get_line(), curr_token.get_offset());
	} else {
	    synchronise(SEMICOLON);
	    parser_errors++;
	    throw ParserError("incomplete variable declaration missing '='",
		    id_token.get_line(), id_token.get_offset());
	}
    } else {
	    synchronise(SEMICOLON);
	    parser_errors++;
	    throw ParserError("expected id after type BOOL",
		    id_token.get_line(), id_token.get_offset());
    }
    return nullptr;
}

Expr* LLParser::expression(){
    return or_expr();
}

Expr* LLParser::or_expr(){
    Expr* left = and_expr(); 
    while(match(OR)){
	Token op = current_token();
	advance();
	Expr* right = and_expr();	
	left = new BinaryExpr(op, left, right);
    }
    return left;
}

Expr* LLParser::and_expr(){
    Expr* left = term(); 
    while(match(AND)){
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
    if (match(INT)) { 
	Expr* inty = new IntExpr(current_token());
	advance();
	return inty;
    }

    if (match(STRING)){
	Expr* stringy = new StringExpr(current_token());
	advance();
	return stringy;
    }

    if (match(DOUBLE)){
	Expr* doubly = new DoubleExpr(current_token());
	advance();
	return doubly;
    }
    
    if (match(ID)){
	Expr* idy = new IdExpr(current_token());
	advance();
	return idy;
    }

    if (match(LEFT_PAR)){
	Token left_par = current_token(); 
	advance();
	Expr* _expr = expression();
	if (!match(RIGHT_PAR)){
	   synchronise(SEMICOLON);
	    parser_errors++;
	   throw ParserError("missing closing parenthesis opened at", left_par.get_line(),
		   left_par.get_offset());
	}
	advance();
	return new GroupingExpr(_expr);
    }
    return nullptr;
}

bool LLParser::match(std::vector<TOKENTYPE> v) const noexcept {
    if (at_end()) return false;
    for (auto& type: v){
	if (type == get_token_type(current)){
	    return true;
	}
    }
    return false;
}

bool LLParser::match(TOKENTYPE type) const noexcept {
    if (at_end()) return false;
    return get_token_type(current) == type;
}

std::string LLParser::tree_to_string() const noexcept {
    std::string final_string;
    for (auto& stmt: stmts){
	final_string += stmt->to_string() + '\n';	
    }
    return final_string;
}

void LLParser::synchronise(TOKENTYPE type){
    if (at_end()) return;
    while (get_token_type(current) != type){
	advance();
    }
    advance();
}
