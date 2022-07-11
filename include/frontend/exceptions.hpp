#pragma once
#include <stdexcept>
#include <string>

class SyntaxError: std::exception {
    std::string msg; 
    int line;
    int column;
    std::string suggestion;
    public:
	explicit SyntaxError(std::string, int line, int column, std::string suggestion);
	explicit SyntaxError(std::string, int line, int column);
	~SyntaxError() override;
	void show_error() const noexcept;
};

class ParserError: std::exception {
    std::string msg;
    int line;
    int column;
    std::string suggestion; 
    public:
	explicit ParserError();
	~ParserError();
	void show_error();
};
