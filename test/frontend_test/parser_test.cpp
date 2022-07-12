#include <gtest/gtest.h>
#include "frontend/lexer.hpp"
#include "frontend/llparser.hpp"
#include "frontend/stmt.hpp"
#include "../xml_support/xml_support.hpp"

class LLParserTest : public ::testing::Test {
    protected:
	LLParserTest() { }
	~LLParserTest() { }

	explicit LLParserTest(std::string s){
	   lexer = new Lexer(s);    
	   parser = new LLParser(lexer->scan_tokens());
	}

	void SetUp(){
	    tree = parser->parse();
	}

	void TearDown() {
	    if (lexer != nullptr){
		delete lexer;
		lexer = nullptr;
	    }

	    if (parser != nullptr){
		delete parser;
		parser = nullptr;
	    }

	    for (auto& stmt: tree){
		delete stmt;
		stmt = nullptr;
	    }
	}

	Lexer* lexer;
	LLParser* parser;
	std::vector<Stmt*> tree;	
};

TEST(ParserFakeTest, helloworld){
    PrintDocument();
}
                             

