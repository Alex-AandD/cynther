#include <iostream>
#include "frontend/exceptions.hpp"

UndefinedCharacter::UndefinedCharacter(char c, size_t l, size_t off)
    :char_wrong(c), line(l), offset(off){ }

void UndefinedCharacter::print_error()
{
    std::cout << ">>> Error: Unexpected Character "
    << line << ":" << offset << '\n'
    << char_wrong << "cannot be recognized\n";
}


UndefinedLiteral::UndefinedLiteral(std::string _type, std::string lex,
				    size_t l, size_t off)
    :type(_type), lexeme(lex), line(l), offset(off){ }

void UndefinedLiteral::print_error()
{
    std::cout << ">>> Error: Undefined Literal "
    << line << ":" << offset << '\n'
    << lexeme << "is not a valid " << type << '\n';
}

MissingClosingQuote::MissingClosingQuote(size_t l, size_t off)
    :line(l), offset(off){ }

void MissingClosingQuote::print_error()
{
    std::cout << ">>> Error: Missing Closing Quote"
    << line << ":" << offset << '\n';
}
