#pragma once
#include <stdexcept>
#include <string>

class Diagnostics : std::exception {
    protected:
	std::string msg; 
	int line;
	int column;
	std::string suggestion;
    public:
	Diagnostics(std::string, int line, int column, std::string suggestion);
	virtual ~Diagnostics();
	virtual void show_error() const noexcept = 0;
};

class SyntaxError: public Diagnostics {
    public:
	explicit SyntaxError(std::string, int line, int column, std::string suggestion);
	explicit SyntaxError(std::string, int line, int column);
	~SyntaxError() override;
	void show_error() const noexcept override;
};

class ParserError: public Diagnostics {
    public:
	explicit ParserError(std::string, int line, int column, std::string suggestion);
	explicit ParserError(std::string, int line, int column);
	~ParserError() override;
	void show_error() const noexcept override;
};
