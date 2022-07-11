#pragma once
#include <iostream>

enum TOKENTYPE {
    INT, DOUBLE, STRING, BOOL, FUNCTION, ID, LEFT_PAR, RIGHT_PAR, LEFT_BRACE,
    RIGHT_BRACE,
    INT_TYPE, DOUBLE_TYPE, STRING_TYPE, BOOL_TYPE,
    QUOTE,
    IF, ELSE, WHILE, FOR, ARROW,
    PLUS, MINUS, SLASH, COMMENT, TIMES, MODULO, 
    EQUAL, NOT_EQUAL, NOT, GT, LT, GTE, LTE, EQUAL_EQUAL, AND, OR,
    SEMICOLON, EOF_
};

class Token {
    private:
	std::string lexeme;	
	TOKENTYPE type;
	size_t line;
	size_t offset;
    public:
	Token(TOKENTYPE, std::string lexeme, size_t line, size_t offset);
	Token();
	// visual representation of the token 
	
	void to_string();

	// some getters
	inline std::string get_lexeme() const { return lexeme; }
	inline size_t get_line() const {return line;}
	inline size_t get_offset() const {return offset;}
	inline TOKENTYPE get_type() const {return type;}
};
