#pragma once
#include <iostream>

enum TOKENTYPE {
    INT, DOUBLE, STRING, BOOL, FUNCTION, ID,
    QUOTE,
    IF, ELSE, WHILE, FOR,
    PLUS, MINUS, SLASH, COMMENT, TIMES, MODULO, 
    EQUAL, NOT_EQUAL, NOT, GT, LT, GTE, LTE, EQUAL_EQUAL,
    SEMICOLON, EOF_
};

class Token {
    private:
	size_t offset;
	size_t line;
	std::string lexeme;	
	TOKENTYPE type;
    public:
	Token(TOKENTYPE, std::string lexeme, size_t line, size_t offset);
	Token();

	// visual representation of the token 
	void __repr__();

	// some getters
	inline std::string getLexeme() const { return lexeme; }
	inline size_t getLine() const {return line;}
	inline size_t getOffset() const {return offset;}
	inline TOKENTYPE getType() const {return type;}
};
