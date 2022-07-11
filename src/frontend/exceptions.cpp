#include <iostream>
#include "frontend/exceptions.hpp"


/*******************************************************************
 * HANDLING SYNTAX ERRORS INSIDE THE LEXER
 * *****************************************************************/
SyntaxError::SyntaxError(std::string _msg, int _line, int _column):
    SyntaxError(_msg, _line, _column, nullptr) { }

SyntaxError::SyntaxError(std::string _msg, int _line, int _column, std::string _sugg):
    msg(_msg), line(_line), column(_column), suggestion(_sugg) { }

void SyntaxError::show_error() const noexcept {
    std::cerr << "Syntax Error: " << msg << " " << line << ":" << column << '\n' <<
    suggestion;
}

/*******************************************************************
 * HANDLING PARSER ERRORS INSIDE
 * *****************************************************************/
ParserError::ParserError(){}
ParserError::~ParserError(){}
