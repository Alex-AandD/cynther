#include <frontend/token.hpp>
#include <iostream>

Token::Token() { }

Token::Token(TOKENTYPE _type, std::string _lex, size_t _line, size_t _offset)
    :lexeme(_lex),type(_type), line(_line), offset(_offset){}

static std::string TOKENTYPE_to_str(TOKENTYPE type){
    switch(type){
	case PLUS: return "PLUS";
	case MINUS: return "MINUS";
	case LEFT_BRACE: return "LEFT_BRACE";
	case RIGHT_BRACE: return "RIGHT_BRACE";
	case INT: return "INT";
	case DOUBLE: return "DOUBLE";
	case BOOL: return "BOOL";
	case STRING: return "STRING";
	case LEFT_PAR: return "LEFT_PAR";
	case RIGHT_PAR: return "RIGHT_PAR";
	case TIMES: return "TIMES";
	case IF: return "IF";
	case LEFT_SQUARE: return "LEFT SQUARE";
	case RIGHT_SQUARE: return "RIGHT SQUARE";
	case SLASH: return "SLASH";
	case SEMICOLON: return "SEMICOLON";
	case ARROW : return "ARROW";
	case EQUAL: return "EQUAL";
	case EQUAL_EQUAL: return "EQUAL_EQUAL";
	case AND: return "AND";
	case OR: return "OR";
	case GT: return "GT";
	case GTE: return "GTE";
	case LT: return "LT";
	case LTE: return "LTE";
	case INT_TYPE: return "INT_TYPE";
	case STRING_TYPE: return "STRING_TYPE";
	case BOOL_TYPE: return "BOOL_TYPE";
	case DOUBLE_TYPE: return "DOUBLE_TYPE";
	case NOT_EQUAL: return "NOT_EQUAL";
	case MODULO: return "MODULO";
	case COMMENT: return "COMMENT";
	case FUNCTION: return "FUNCTION";
	case EOF_: return "EOF";
	case ID: return "ID";
	default: return "UNKNOWN";
    }
}

void Token::to_string(){
    std::cout << TOKENTYPE_to_str(type) << ' ';
    std::cout << lexeme << ' ';
    std::cout << line << ':' << offset << '\n';
}
