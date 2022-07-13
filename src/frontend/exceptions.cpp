#include <iostream>
#include "frontend/exceptions.hpp"

Diagnostics::Diagnostics(std::string _msg, int _line, int _column, std::string _sugg)
   : msg(_msg), line(_line), column(_column), suggestion(_sugg) { }
Diagnostics::~Diagnostics(){ }

/*******************************************************************
 * HANDLING SYNTAX ERRORS INSIDE THE LEXER
 * *****************************************************************/
SyntaxError::SyntaxError(std::string _msg, int _line, int _column):
    Diagnostics(_msg, _line, _column, ""), color(CYAN) { }

SyntaxError::SyntaxError(std::string _msg, int _line, int _column, std::string _sugg):
    Diagnostics(_msg, _line, _column, _sugg), color(CYAN){}
SyntaxError::~SyntaxError(){ }

void SyntaxError::show_error() const noexcept {
    std::cerr << color << "Syntax Error: " << msg << " " << line << ":" << column << '\n' <<
    suggestion << RESET_COLOR;
}

/*******************************************************************
 * HANDLING PARSER ERRORS INSIDE
 * *****************************************************************/
ParserError::ParserError(std::string _msg, int _line, int _column)
    :Diagnostics(_msg, _line, _column, ""), color(RED) { }

ParserError::ParserError(std::string _msg, int _line, int _column, std::string _sugg)
    :Diagnostics(_msg, _line, _column, _sugg), color(RED) { }

ParserError::~ParserError() { }

void ParserError::show_error() const noexcept {
    std::cerr << color << "Parser Error: " << msg << " " << line << ":" << column << '\n' <<
    suggestion << RESET_COLOR;
}
