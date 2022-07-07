#include "frontend/lexer.hpp"
#include <iostream>
#include <fstream>

size_t get_file_size(FILE* file){
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);
    return size;
}

int main(int argc, char *argv[]){
    const char* filename;
    FILE* file;
    if (argc > 1){
	filename = argv[1];
    } else {
	return 0;
    }
    file = fopen(filename, "r");
    size_t len = get_file_size(file);
    if (len == 0) { 
	std::cout << "file is empty"; 
	return 0;
    }

    char buffer[len];
    std::cout << buffer << '\n';
    fread(buffer, 1, len, file);
    std::string input_string{buffer};

    Lexer lexer(input_string);
    auto tokens = lexer.scan_tokens();
    lexer.__repr__();
    
    fclose(file);
}
