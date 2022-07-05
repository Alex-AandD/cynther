#include <iostream>
#include "frontend/lexer.hpp"
#include "frontend/exceptions.hpp"

Lexer::Lexer(std::string input):
    input_string(input), start(0), current(0), line(1){ }

Lexer::~Lexer(){ }

bool Lexer::match(char c){
    return peek_next() == c;
}

char Lexer::peek_next(){
    if (!at_end()) return input_string[current + 1];
    return -1;
}

bool Lexer::at_end(){
    return current < input_string.size();
}

bool static isname(char c){
    return  std::isalpha(c) || c == '_';
}

std::vector<Token> Lexer::scan_tokens(){
    while(!at_end()){
	start = current;
	char c_char {input_string[current]};
	Token t;
	switch(c_char){
	    case ' ':
	    case '\t':
	    case '\r':break;
	    case '\n':line++;break;
	    case ';': t = push_simple_token(SEMICOLON); break;
	    case '=': match('=') ? push_simple_token(EQUAL_EQUAL) : 
		      push_simple_token(EQUAL);break;
	    case '+': push_simple_token(PLUS);break;
	    case '-': push_simple_token(MINUS);break;
	    case '*': push_simple_token(TIMES);break;
	    case '/': match('/') ? push_comment_token() :
		      push_simple_token(SLASH);break;
	    case '>': match('=') ? push_simple_token(GTE) : 
		      push_simple_token(GT);break;
	    case '<': match('=') ? push_simple_token(LTE) : 
		      push_simple_token(LT);break;
	    case '!': match('=') ? push_simple_token(NOT_EQUAL) : 
		      push_simple_token(NOT);break;
	    default:
		    if (std::isdigit(c_char)) push_number_token();break;
		    if (isname(c_char)) push_string_token();break;
		    throw UndefinedCharacter(c_char, line, current);
	}
	current++;
    }
}

void Lexer::push_token(Token t){
    tokens.push_back(t);
}

Token Lexer::push_simple_token(TOKENTYPE token_type)
{	
    return Token(token_type, input_string.substr(current, 1), line, current);
}

Token Lexer::push_comment_token()
{
   while(input_string[current] != '\n'){
	current++;
   }
   return Token(COMMENT, input_string.substr(start, current - start),
	   line, start);
}

// TODO: finish to scan integers
Token Lexer::push_int_token()
{
    while(std::isdigit(input_string[current])){
	current++;	
    }
}

// TODO: finish to scan double
Token Lexer::push_double_token()
{

}

// TODO: finish to scan string
Token Lexer::push_string_token()
{
    
}
