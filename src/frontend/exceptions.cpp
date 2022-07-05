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
