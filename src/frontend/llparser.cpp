#include "frontend/llparser.hpp"
#include "frontend/stmt.hpp"
#include "frontend/expression.hpp"
#include "frontend/exceptions.hpp"

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
	    Stmt* stmt = declaration();
	    stmts.push_back(stmt);
	} catch(ParserError& err){
	    inc_errors();
	    err.show_error();
	}
    }
}

/********************************************/
/************* DECLARATIONS *****************/
/********************************************/

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

    return statement();	
}

Stmt* LLParser::int_declaration(){
    Token id_token = current_token();
    if (match(ID)){
	advance();
    } else {
	panic_mode(id_token, RIGHT_BRACE);
	throw ParserError("expected id after type INT", line_error(), column_error());
    }

    if (match(EQUAL)){
	advance();
    } else {
	panic_mode(id_token, RIGHT_BRACE);
        throw ParserError("incomplete variable declaration missing '='", line_error(), column_error());
    }

    Expr* expr = expression();
    if (match(SEMICOLON)){
	advance();
	return new StringDeclarationStmt(id_token, expr);
    } else {
	panic_mode(RIGHT_BRACE);
	throw ParserError("missing semicolon after string declaration", line_error(), column_error());
    }
    return nullptr;
}

Stmt* LLParser::double_declaration(){
    Token id_token = current_token();
    if (match(ID)){
	advance();
    } else {
	panic_mode(id_token, RIGHT_BRACE);
	throw ParserError("expected id after type DOUBLE", line_error(), column_error());
    }

    if (match(EQUAL)){
	advance();
    } else {
	panic_mode(id_token, RIGHT_BRACE);
        throw ParserError("incomplete variable declaration missing '='", line_error(), column_error());
    }

    Expr* expr = expression();
    if (match(SEMICOLON)){
	advance();
	return new StringDeclarationStmt(id_token, expr);
    } else {
	panic_mode(RIGHT_BRACE);
	throw ParserError("missing semicolon after string declaration", line_error(), column_error());
    }
    return nullptr;
}

Stmt* LLParser::string_declaration(){
    Token id_token = current_token();
    if (match(ID)){
	advance();
    } else {
	panic_mode(id_token, RIGHT_BRACE);
	throw ParserError("expected id after type STRING", line_error(), column_error());
    }

    if (match(EQUAL)){
	advance();
    } else {
	panic_mode(id_token, RIGHT_BRACE);
        throw ParserError("incomplete variable declaration missing '='", line_error(), column_error());
    }

    Expr* expr = expression();
    if (match(SEMICOLON)){
	advance();
	return new StringDeclarationStmt(id_token, expr);
    } else {
	panic_mode(RIGHT_BRACE);
	throw ParserError("missing semicolon after string declaration", line_error(), column_error());
    }
    return nullptr;
}

Stmt* LLParser::bool_declaration(){
    Token id_token = current_token();
    if (match(ID)){
	advance();
    } else {
	panic_mode(id_token, RIGHT_BRACE);
	throw ParserError("expected id after type BOOL", line_error(), column_error());
    }

    if (match(EQUAL)){
	advance();
    } else {
	panic_mode(id_token, RIGHT_BRACE);
        throw ParserError("incomplete variable declaration missing '='", line_error(), column_error());
    }

    Expr* expr = expression();
    if (match(SEMICOLON)){
	advance();
	return new StringDeclarationStmt(id_token, expr);
    } else {
	panic_mode(RIGHT_BRACE);
	throw ParserError("missing semicolon after string declaration", line_error(), column_error());
    }
    return nullptr;
}

/********************************************/
/**************** STATEMENT *****************/
/********************************************/

Stmt* LLParser::statement(){
    if (match(FUNCTION)){
	advance();								
	return fun_statement();
    }

    if (match(IF)){
	advance();
	return if_statement();
    }

    if (match(WHILE)){
	advance();
	return while_statement();
    }

    if (match(LEFT_BRACE)){
	advance();
	return block();
    }

    if (match(RETURN)){
	advance();
	return return_statement();		
    }

    return assignment_statement();
}

Stmt* LLParser::fun_statement(){
    FunctionStmt* fun_statement = new FunctionStmt();
    if (match(ID)){
	advance();
    } else {
	panic_mode(RIGHT_PAR);
	throw ParserError("expected id after fun keyword", line_error(), column_error());
    }

    if (match(LEFT_PAR)){
	if (get_token_type(current+1) == RIGHT_PAR){
	   advance();
	} else {
	    fun_args(fun_statement);
	}
    }

    if (match(RIGHT_PAR)){
	advance();
    } else {
	panic_mode(LEFT_BRACE);
	throw ParserError("expected closing parenthesis after argument list",
		line_error(), column_error());
    }

    if (match(ARROW)){
	advance();
    } else {
	panic_mode(LEFT_BRACE);
	throw ParserError("expected arrow after argument list",
		line_error(), column_error());
    }

    if (match({INT_TYPE, STRING_TYPE, BOOL_TYPE, DOUBLE_TYPE})){
	fun_statement->set_return_type(get_token_type(current));
	advance();
    } else {
	panic_mode(LEFT_BRACE);
	throw ParserError("expected return type after function definition",
		line_error(), column_error());
    }

    if (match(LEFT_BRACE)){
	advance();
	fun_statement->set_body(block());
	return fun_statement;
    } else {
	panic_mode(RIGHT_BRACE);
	throw ParserError("expected opening brace after function declaration",
		line_error(), column_error());
    }

    return nullptr;
}

void LLParser::fun_args(FunctionStmt* stmt){
    do {
	advance();
	if (match({INT_TYPE, STRING_TYPE, BOOL_TYPE, DOUBLE_TYPE})){
	    stmt->push_type(get_token_type(current));
	    advance();
	} else {
	    panic_mode(RIGHT_PAR);
	    throw ParserError("expected argument type", line_error(), column_error());
	}
	if (match(ID)){
	    stmt->push_arg(current_token());
	    advance();
	} else {
	    panic_mode(RIGHT_PAR);
	    throw ParserError("Expected id after argument type", line_error(), column_error());
	}
    } while(match(COMA));
};

Stmt* LLParser::return_statement(){
    Expr* value = expression();
    if (match(SEMICOLON)){
	advance();
	return new ReturnStmt(value);
    } else {
	panic_mode(RIGHT_BRACE);
	throw ParserError("expected semicolon at the end of return statement", 
		line_error(), column_error());
    }
    return nullptr;
}

Stmt* LLParser::while_statement(){
    Expr* condition = expression();
    //Token token = current_token();
    if (match(ARROW)){
	advance();
	if (match(LEFT_BRACE)){
	    advance();
	    Stmt* body = block();
	    return new WhileStmt(condition, body);
	} else {
	  panic_mode(RIGHT_BRACE);
	  throw ParserError("missing left brace after arrow", line_error(), column_error());
	}
    } else {
	panic_mode(RIGHT_BRACE);
	throw ParserError("expected arrow after condition", line_error(), column_error());
    }
    return nullptr;
}

Stmt* LLParser::if_statement(){
    Expr* condition = expression();
    //Token token = current_token();
    if (match(ARROW)){
	advance();
	if (match(LEFT_BRACE)){
	    advance();
	    Stmt* body = block();
	    return new IfStmt(condition, body);
	} else {
	    panic_mode(RIGHT_BRACE);
	    throw ParserError("missing left brace after arrow", line_error(), column_error());
	}
    } else {
	panic_mode(RIGHT_BRACE);
	throw ParserError("expected arrow after condition", line_error(), column_error());
    }
    return nullptr;
}

Stmt* LLParser::block(){
    std::vector<Stmt*> v_stmts;
    while(!match(RIGHT_BRACE)){
	v_stmts.push_back(declaration());
    }
    if (at_end()) {
	set_error();
	throw ParserError("missing right brace", line_error(), column_error());
	exit(1);
    } else {
	advance();
	return new BlockStmt(v_stmts);
    }
    return nullptr;
}

Stmt* LLParser::assignment_statement(){
    Token id_token = current_token(); 
    if (match(ID)){
	advance();	
    } else {
	panic_mode(SEMICOLON);
	throw ParserError("expected statement", line_error(), column_error());
    }

    if (match(EQUAL)){
	advance();
	Expr* expr = expression();
	return new AssignmentStmt(id_token, expr);
    } else {
	panic_mode(SEMICOLON);
	throw ParserError("expected assignment statement", line_error(), column_error());
    }
    return nullptr;
}

/********************************************/
/*************** EXPRESSION *****************/
/********************************************/

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
    Expr* left = equality(); 
    while(match(AND)){
	Token op = current_token();
	advance();
	Expr* right = equality();	
	left = new BinaryExpr(op, left, right);
    }
    return left;
}

Expr* LLParser::equality(){
    Expr* left = comparison();
    while(match({EQUAL_EQUAL, NOT_EQUAL})){
	Token op = current_token();
	advance(); 	
	Expr* right = comparison();
	left = new BinaryExpr(op, left, right);	
    }
    return left;
}

Expr* LLParser::comparison(){
    Expr* left = term();
    while(match({GT, GTE, LT, LTE})){
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
	if (match(RIGHT_PAR)){
	    advance();
	    return new GroupingExpr(_expr);
	} else {
	    panic_mode(left_par, LEFT_BRACE);
	    throw ParserError("missing closing parenthesis opened at", line_error(), column_error());
	}
    }
    return nullptr;
}

/*******************************************/
/************** UTILITY ********************/
/*******************************************/

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

void LLParser::panic_mode(TOKENTYPE sync_point) noexcept {
    set_error();
    synchronise(sync_point);
}

void LLParser::panic_mode(Token t, TOKENTYPE sync_point) noexcept {
    set_error(t);
    synchronise(sync_point);
}

void LLParser::synchronise(TOKENTYPE type){
    while (!at_end() && get_token_type(current) != type){
	advance();
    }
    advance();
}
