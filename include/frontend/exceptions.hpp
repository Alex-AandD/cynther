#pragma once
#include <stdexcept>
#include <string>
#define RESET_COLOR   "\033[0m"
#define RED "\033[31m"
#define CYAN "\033[36m"


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
    private:
	std::string color;	
    public:
	explicit SyntaxError(std::string, int line, int column, std::string suggestion);
	explicit SyntaxError(std::string, int line, int column);
	~SyntaxError() override;
	void show_error() const noexcept override;
};

class ParserError: public Diagnostics {
    private:
	std::string color;	
    public:
	explicit ParserError(std::string, int line, int column, std::string suggestion);
	explicit ParserError(std::string, int line, int column);
	~ParserError() override;
	void show_error() const noexcept override;
};
