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
	if (match(LEFT_SQUARE)){
	    advance();
	    return int_list_declaration(); 
	}
	return int_declaration();}

    if (match(STRING_TYPE)){
	advance();
	if (match(LEFT_SQUARE)){
	    advance();
	    return string_list_declaration();
	}
	return string_declaration();}

    if (match(BOOL_TYPE)){
	advance();
	if (match(LEFT_SQUARE)){
	    advance();
	    return bool_list_declaration();
	}
	return bool_declaration();}

    if (match(DOUBLE_TYPE)){
	advance();
	if (match(LEFT_SQUARE)){
	    advance();
	    return double_list_declaration();
	}
	return double_declaration();}

    if (match(SEMICOLON)){
	advance();
	return nullptr;
    }

    return statement();	
}

/***********************************
 * LIST DECLARATIONS
 ***********************************/

Stmt* LLParser::int_list_declaration(){
    Expr* num_values = expression();
    if (!match(RIGHT_SQUARE)){
	panic_mode(SEMICOLON);
	throw ParserError("missing closing bracket after number of values",
		line_error(), column_error());}
    advance();
    Expr* id = expression();

    if (match(SEMICOLON)){
	advance();
	return new IntListStmt(id, num_values, nullptr);
    }

    if (!match(EQUAL)){
	panic_mode(SEMICOLON);
	throw ParserError("expecting integer list definition", line_error(), column_error());}
    
    advance();
    Expr* values = expression();
    if (!match(SEMICOLON)){
	panic_mode(SEMICOLON);
	throw ParserError("expecting semicolon at the end of integer list definition",
		line_error(), column_error());}
    advance();
    return new IntListStmt(id, num_values, values);
}

Stmt* LLParser::string_list_declaration(){
    Expr* num_values = expression();
    if (!match(RIGHT_SQUARE)){
	panic_mode(SEMICOLON);
	throw ParserError("missing closing bracket after number of values",
		line_error(), column_error());}
    advance();
    Expr* id = expression();

    if (match(SEMICOLON)){
	advance();
	return new StringListStmt(id, num_values, nullptr);
    }

    if (!match(EQUAL)){
	panic_mode(SEMICOLON);
	throw ParserError("expecting string list definition",
		line_error(), column_error());}
    
    advance();
    Expr* values = expression();
    if (!match(SEMICOLON)){
	panic_mode(SEMICOLON);
	throw ParserError("expecting semicolon at the end of string list definition",
		line_error(), column_error());}
    advance();
    return new StringListStmt(id, num_values, values);
}

Stmt* LLParser::double_list_declaration(){
    Expr* num_values = expression();
    if (!match(RIGHT_SQUARE)){
	panic_mode(SEMICOLON);
	throw ParserError("missing closing bracket after number of values",
	    line_error(), column_error());}
    advance();
    Expr* id = expression();

    if (match(SEMICOLON)){
	advance();
	return new DoubleListStmt(id, num_values, nullptr);
    }

    if (!match(EQUAL)){
	panic_mode(SEMICOLON);
	throw ParserError("expecting double list definition",
		line_error(), column_error());}
    advance();
    Expr* values = expression();
    if (!match(SEMICOLON)){
	panic_mode(SEMICOLON);
	throw ParserError("expecting semicolon at the end of double list definition",
		line_error(), column_error());}
    advance();
    return new DoubleListStmt(id, num_values, values);
}

Stmt* LLParser::bool_list_declaration(){
    Expr* num_values = expression();

    if (!match(RIGHT_SQUARE)){
	panic_mode(SEMICOLON);
	throw ParserError("missing closing bracket after number of values",
		line_error(), column_error());}
    advance();

    Expr* id = expression();

    if (match(SEMICOLON)){
	advance();
	return new BoolListStmt(id, num_values, nullptr);
    }

    if (!match(EQUAL)){
	panic_mode(SEMICOLON);
	throw ParserError("expecting bool list definition",
		line_error(), column_error());}
    
    advance();
    Expr* values = expression();
    if (!match(SEMICOLON)){
	panic_mode(SEMICOLON);
	throw ParserError("expecting semicolon at the end of bool list definition",
		line_error(), column_error());}
    advance();
    return new BoolListStmt(id, num_values, values);
}

/***************************************
 * "NORMAL" DECLARATIONS
 * *************************************/

Stmt* LLParser::int_declaration(){
    Expr* id_expr;
    if (match(ID)){
	id_expr = expression();
    } else {
	panic_mode(RIGHT_BRACE);
	throw ParserError("expected id after type INT", line_error(), column_error());
    }

    if (match(SEMICOLON)){
	advance();	
	return new ExprStmt(id_expr);
    }

    if (match(EQUAL)){
	advance();
    } else {
	panic_mode(RIGHT_BRACE);
        throw ParserError("incomplete variable declaration missing '='", line_error(), column_error());
    }

    Expr* expr = expression();

    if (match(SEMICOLON)){
	advance();
	return new IntDeclarationStmt(id_expr, expr);
    } else {
	panic_mode(RIGHT_BRACE);
	throw ParserError("missing semicolon after INT declaration", line_error(), column_error());
    }
    return nullptr;
}

Stmt* LLParser::double_declaration(){
    Expr* id_expr;
    if (match(ID)){
	id_expr = expression();
    } else {
	panic_mode(RIGHT_BRACE);
	throw ParserError("expected id after type DOUBLE", line_error(), column_error());
    }
    	 
    if (match(SEMICOLON)){
	advance();	
	return new ExprStmt(id_expr);
    }

    if (match(EQUAL)){
	advance();
    } else {
	panic_mode(RIGHT_BRACE);
        throw ParserError("incomplete variable declaration missing '='", line_error(), column_error());
    }

    Expr* expr = expression();

    if (match(SEMICOLON)){
	advance();
	return new DoubleDeclarationStmt(id_expr, expr);
    } else {
	panic_mode(RIGHT_BRACE);
	throw ParserError("missing semicolon after DOUBLE declaration", line_error(), column_error());
    }
    return nullptr;
}

Stmt* LLParser::string_declaration(){
    Expr* id_expr;
    if (match(ID)){
	id_expr = expression();
    } else {
	panic_mode(RIGHT_BRACE);
	throw ParserError("expected id after type STRING", line_error(), column_error());
    }
    	 
    if (match(SEMICOLON)){
	advance();	
	return new ExprStmt(id_expr);
    }

    if (match(EQUAL)){
	advance();
    } else {
	panic_mode(RIGHT_BRACE);
        throw ParserError("incomplete variable declaration missing '='", line_error(), column_error());
    }

    Expr* expr = expression();

    if (match(SEMICOLON)){
	advance();
	return new StringDeclarationStmt(id_expr, expr);
    } else {
	panic_mode(RIGHT_BRACE);
	throw ParserError("missing semicolon after string declaration", line_error(), column_error());
    }
    return nullptr;
}

Stmt* LLParser::bool_declaration(){
    Expr* id_expr;
    if (match(ID)){
	id_expr = expression();
    } else {
	panic_mode(RIGHT_BRACE);
	throw ParserError("expected id after type BOOL", line_error(), column_error());
    }

    if (match(SEMICOLON)){
	advance();	
	return new ExprStmt(id_expr);
    }

    if (match(EQUAL)){
	advance();
    } else {
	panic_mode(RIGHT_BRACE);
        throw ParserError("incomplete variable declaration missing '='", line_error(), column_error());
    }

    Expr* expr = expression();

    if (match(SEMICOLON)){
	advance();
	return new BoolDeclarationStmt(id_expr, expr);
    } else {
	panic_mode(RIGHT_BRACE);
	throw ParserError("missing semicolon after bool declaration", line_error(), column_error());
    }
    return nullptr;
}

/********************************************
 * STATEMENTS
 ********************************************/

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
    Expr* id_expr = primary();
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

    fun_statement->set_return_type(resolve_type());

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

TOKENTYPE LLParser::resolve_type(){
    if (match(INT_TYPE)){
	advance();
	if (!match(LEFT_SQUARE)) {return INT_TYPE;}
	advance();
	if (!match(RIGHT_SQUARE)){
	    panic_mode(RIGHT_PAR);
	    throw ParserError("expected closing bracket after int type", line_error(), column_error());
	}
	advance();
	return INT_LIST_TYPE;
    }

    if (match(STRING_TYPE)){
	advance();
	if (!match(LEFT_SQUARE)) {return STRING_TYPE;}
	advance();
	if (!match(RIGHT_SQUARE)){
	    panic_mode(RIGHT_PAR);
	    throw ParserError("expected closing bracket after string type", line_error(), column_error());
	}
	advance();
	return STRING_LIST_TYPE;
    }
    if (match(DOUBLE_TYPE)){
	advance();
	if (!match(LEFT_SQUARE)) {return BOOL_TYPE;}
	advance();
	if (!match(RIGHT_SQUARE)){
	    panic_mode(RIGHT_PAR);
	    throw ParserError("expected closing bracket after bool type", line_error(), column_error());
	}
	advance();
	return BOOL_LIST_TYPE;
    }
    if (match(BOOL_TYPE)){
	advance();
	if (!match(LEFT_SQUARE)) {return BOOL_TYPE;}
	advance();
	if (!match(RIGHT_SQUARE)){
	    panic_mode(RIGHT_PAR);
	    throw ParserError("expected closing bracket after bool type", line_error(), column_error());
	}
	advance();
	return BOOL_LIST_TYPE;
    }

    panic_mode(RIGHT_PAR);
    throw ParserError("expected type in argument list", line_error(), column_error());

}

void LLParser::fun_args(FunctionStmt* stmt){
    do {
	advance();
	stmt->push_type(resolve_type());
	stmt->push_arg(expression());
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
    Expr* id_expr = expression();
    if (match(EQUAL)){
	advance();
	Expr* expr = expression();
	if(match(SEMICOLON)){
	    advance();
	    return new AssignmentStmt(id_expr, expr);
	} else {
	    panic_mode(SEMICOLON);
	    throw ParserError("expected semicolon after assignment", line_error(), column_error());
	}
    }
    if(match(SEMICOLON)){
	advance();
	return new CallStmt(id_expr);
    } else {
	panic_mode(SEMICOLON);
	throw ParserError("expected statement", line_error(), column_error());
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
    return call_expr();
}

Expr* LLParser::call_expr() {
    Expr* expr = primary();
    if (match(LEFT_PAR)){
	std::vector<Expr*> params;
	do {
	   advance();
	   params.push_back(expression());
	} while(match(COMA));
	
	if (match(RIGHT_PAR)){
	    advance();
	    return new CallExpr(expr, params);
	} else {
	   throw ParserError("close parenthesis after function call", line_error(), column_error()); 
	   exit(1);
	}
    }
    return expr;
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

    if (match(LEFT_SQUARE)){
	std::vector<Expr*> values;
	do {
	    advance(); 
	    values.push_back(expression()); 
	} while(match(COMA));

	if (match(RIGHT_SQUARE)){
	    advance();
	    return new ListExpr(values);
	}
	panic_mode(SEMICOLON);	
	throw ParserError("expected closing bracket after values", line_error(), column_error());
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
