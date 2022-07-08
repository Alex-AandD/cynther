#include <iostream>
#include "frontend/lexer.hpp"
#include "frontend/exceptions.hpp"

Lexer::Lexer(): current(0), start(0), line(1), lexer_errors(0){ }
Lexer::Lexer(std::string input):
    current(0), start(0), line(1), input_string(input), lexer_errors(0) { }

Lexer::~Lexer(){ }

std::unordered_map<std::string, TOKENTYPE> Lexer::keyword_map = {
    {"if", IF}, 
    {"else", ELSE}, 
    {"for", FOR}, 
    {"while", WHILE}, 
    {"int", INT_TYPE}, 
    {"bool", BOOL_TYPE}, 
    {"string", STRING_TYPE}, 
    {"double", DOUBLE_TYPE}, 
    {"fun", FUNCTION},
};

bool Lexer::match(char c){
    bool condition {peek_next() == c};
    if (condition) current++;
    return condition;
}

char Lexer::peek_next(){
    if (current + 1 < input_string.size()) return input_string[current + 1];
    return -1;
}

bool Lexer::at_end(){
    return current > input_string.size();
}

bool static isname(char c){
    return  std::isalpha(c) || c == '_';
}

std::vector<Token> Lexer::scan_tokens(){
    while(!at_end()){
	start = current;
	char c_char {input_string[current]};
	try {
	    switch(c_char){
		case ' ':
		case '\t':
		case '\r':break;
		case '\n':line++;break;
		case ';': push_simple_token(SEMICOLON); break;

		case '=': match('=') ? push_simple_token(EQUAL_EQUAL) :
			  match('>') ? push_simple_token(ARROW) :
			  push_simple_token(EQUAL); break;

		case '+': push_simple_token(PLUS); break;
		case '"': start++;current++; push_string_token(); break;
		case '(': push_simple_token(LEFT_PAR); break;
		case ')': push_simple_token(RIGHT_PAR); break;
		case '{': push_simple_token(LEFT_BRACE);break;
		case '}': push_simple_token(RIGHT_BRACE);break;
		case '-': push_simple_token(MINUS);break;
		case '*': push_simple_token(TIMES);break;
		case '/': match('/') ? push_comment_token() : push_simple_token(SLASH);break;
		case '>': match('=') ? push_simple_token(GTE) : push_simple_token(GT);break;
		case '<': match('=') ? push_simple_token(LTE) : push_simple_token(LT);break;
		case '!': match('=') ? push_simple_token(NOT_EQUAL) : push_simple_token(NOT);break;
		case '%': push_simple_token(MODULO);break;
		default:
			if (std::isdigit(c_char)){
			    push_number_token();break;}
			if (isname(c_char)) 
			    push_id_token();break;
			throw UndefinedCharacter(c_char, line, current);
		}
	} catch(UndefinedCharacter& exc){
	    exc.print_error();
	}
	current++;
    }
    return tokens;
}

void Lexer::push_simple_token(TOKENTYPE token_type)
{	
    auto token = Token(token_type, input_string.substr(start, current - start + 1), line, current);
    tokens.push_back(token); 
}

void Lexer::push_comment_token()
{
   while(input_string[current] != '\n' && !at_end()){
	current++;
   }
   auto token = Token(COMMENT, input_string.substr(start, current - start), line, start);
   tokens.push_back(token); 
}

void Lexer::push_number_token(){
    while(!at_end() && std::isdigit(input_string[current])){
	current++;	
    }
    if (input_string[current] == '.'){
	current++;
	return push_double_token();
    }
    return push_int_token();
}

void Lexer::push_int_token()
{
    try{
	if (isname(input_string[current])){ 
	    throw UndefinedLiteral("integer", input_string.substr(start, current -  start + 1),
		  line, current);
	}
	std::string lexeme = input_string.substr(start, current - start);
	auto token = Token(INT, lexeme, line, current);
	tokens.push_back(token);
    } catch(UndefinedLiteral& und){
	und.print_error();
	lexer_errors++;
    }

    current--;
}

void Lexer::push_double_token()
{
    try {
	while(!at_end() && std::isdigit(input_string[current])){
	    current++;
	}
	std::string lexeme = input_string.substr(start, current - start);
	auto token = Token(DOUBLE, lexeme, line, current);
	tokens.push_back(token);

    } catch(UndefinedLiteral& und){
	und.print_error();
	lexer_errors++;
    }
    current--;
}

void Lexer::push_string_token(){
    while(!at_end() && input_string[current] != '"') {
	current++;
    }
    if (at_end()) throw MissingClosingQuote(line, start);
    std::string lexeme = input_string.substr(start, current - start);
    auto token = Token(STRING, lexeme, line, start); // using start, probably in the future both 
						     // start and current will be needed to get 
						     // better error handling.
    tokens.push_back(token);
}

void Lexer::push_id_token()
{
   try {
       while(!at_end() && isname(input_string[current])){
	    current++;
	}
	if (std::isdigit(input_string[current])){ 
	    throw UndefinedLiteral("id", input_string.substr(start, current -  start + 1),
				    line, current); }

	std::string lexeme = input_string.substr(start, current - start);
	auto keyword_it = keyword_map.find(lexeme);
	if (keyword_it != keyword_map.end()){
	    tokens.push_back(Token(keyword_it -> second, lexeme, line, current)); }
	else {
	    tokens.push_back(Token(ID, lexeme, line, current));}
       } catch(UndefinedLiteral& und){
	    und.print_error();
	    lexer_errors++;
       }
    current--;
}

void Lexer::__repr__(){
    std::cout << "NUMBER OF TOKENS: " << tokens.size() << '\n';
    for (auto& token: tokens){
	token.__repr__();
    }
}

std::vector<TOKENTYPE> Lexer::get_types() const {
    std::vector<TOKENTYPE> vec;
    for (auto& token: tokens){
	vec.push_back(token.get_type());
    }
    return vec;
}

std::vector<std::string> Lexer::get_lexemes() const {
    std::vector<std::string> vec;
    for (auto& token: tokens){
	vec.push_back(token.get_lexeme());
    }
    return vec;
}
