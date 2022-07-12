#include <iostream>
#include "frontend/exceptions.hpp"

Diagnostics::Diagnostics(std::string _msg, int _line, int _column, std::string _sugg)
   : msg(_msg), line(_line), column(_column), suggestion(_sugg) { }
Diagnostics::~Diagnostics(){ }

/*******************************************************************
 * HANDLING SYNTAX ERRORS INSIDE THE LEXER
 * *****************************************************************/
SyntaxError::SyntaxError(std::string _msg, int _line, int _column):
    Diagnostics(_msg, _line, _column, "") { }

SyntaxError::SyntaxError(std::string _msg, int _line, int _column, std::string _sugg):
    Diagnostics(_msg, _line, _column, _sugg){}
SyntaxError::~SyntaxError(){ }

void SyntaxError::show_error() const noexcept {
    std::cerr << "Syntax Error: " << msg << " " << line << ":" << column << '\n' <<
    suggestion;
}

/*******************************************************************
 * HANDLING PARSER ERRORS INSIDE
 * *****************************************************************/
ParserError::ParserError(std::string _msg, int _line, int _column)
    :Diagnostics(_msg, _line, _column, "") { }

ParserError::ParserError(std::string _msg, int _line, int _column, std::string _sugg)
    :Diagnostics(_msg, _line, _column, _sugg) { }

ParserError::~ParserError() { }

void ParserError::show_error() const noexcept {
    std::cerr << "Parser Error: " << msg << " " << line << ":" << column << '\n' <<
    suggestion;
}
