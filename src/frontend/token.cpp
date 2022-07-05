#include <frontend/token.hpp>
#include <iostream>

Token::Token() { }

Token::Token(TOKENTYPE _type, std::string _lex, size_t _line, size_t _offset)
    :type(_type), lexeme(_lex), line(_line), offset(_offset){}

Token::~Token(){ }


static std::string TOKENTYPE_to_str(TOKENTYPE type){
    switch(type){
	case PLUS: return "PLUS";
	case MINUS: return "MINUS";
	case TIMES: return "TIMES";
	case SLASH: return "SLASH";
	case MODULO: return "MODULO";
	case SEMICOLON: return "SEMICOLON";
	case COMMENT: return "COMMENT";
	case EQUAL: return "EQUAL";
	case EQUAL_EQUAL: return "EQUAL_EQUAL";
	case GT: return "GT";
	case GTE: return "GTE";
	case LT: return "LT";
	case LTE: return "LTE";
	case NOT_EQUAL: return "NOT_EQUAL";
	case INT: return "INT";
	case DOUBLE: return "DOUBLE";
	case BOOL: return "BOOL";
	case STRING: return "STRING";
	case EOF_: return "EOF";
	default: return "UNKNOWN";
    }
}

void Token::__repr__(){
    std::cout << TOKENTYPE_to_str(type) << ' ';
    std::cout << "lex:" << lexeme << ' ';
    std::cout << line << ':' << offset << '\n';
}
