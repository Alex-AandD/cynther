#include "frontend/lexer.hpp"
#include <gtest/gtest.h>

TEST(LexerTest, CorrectLength){
    std::string test_string = "int number = 9";
    Lexer lexer(test_string);
    auto tokens = lexer.scan_tokens();
    EXPECT_EQ(4, tokens.size());    

    Lexer lexer2("");
    tokens = lexer2.scan_tokens();
    EXPECT_EQ(0, tokens.size());

    test_string =
	"string my_string = \"hello world\"\n" 
	"int my_int = 9 \n"
	"if \"hello\"";
    
    Lexer lexer3(test_string); 
    tokens = lexer3.scan_tokens();
    EXPECT_EQ(10, tokens.size());
}

// checking integer literals and integer operands
TEST(LexerTest, CorrectTypes){
    std::string test_string =
	"int number = 89 * 98.23 + 34 + 0.12 % 400000 * 0 \n"
	"double _new_number = 90 + 432 + 0.231\n % 45 \n/ 10021.2134234\n";
    Lexer lexer(test_string);
    auto tokens = lexer.scan_tokens();
    std::vector<TOKENTYPE> types = lexer.get_types();
    std::vector<TOKENTYPE> expected_types {
	INT_TYPE, ID, EQUAL, INT, TIMES, DOUBLE, PLUS, INT,
	PLUS, DOUBLE, MODULO, INT, TIMES, INT, DOUBLE_TYPE, ID,
	EQUAL, INT, PLUS, INT, PLUS, DOUBLE, MODULO, INT, SLASH, DOUBLE
    };
    
    EXPECT_EQ(types, expected_types);  
    test_string = 
	"string my_string = \"hello world\"\n"
	"// this is a comment nothing to see here\n"
	"// this is another comment nothing to see here either\n"
	"if my_string == \"hello world\""
	"for int i = 0 \"hello world\";";
    Lexer lexer2(test_string); 
    tokens = lexer2.scan_tokens();
    types = lexer2.get_types();
    expected_types = {
	STRING_TYPE, ID, EQUAL, STRING,
	COMMENT,
	COMMENT,
	IF, ID, EQUAL_EQUAL, STRING,
	FOR, INT_TYPE, ID, EQUAL, INT, STRING, SEMICOLON
    };
}

TEST(LexerTest, CorrectLexemes){
    std::string test_string = 
	"8 % 4 if else int \"hello world\""
	"653.1232 + 231.1234 * 43.12 / 3432"	
	"// hello world this is a comment\n"
	"int double string";

    std::vector<std::string> expected_lexemes = {
	"8", "%", "4", "if", "else", "int", "hello world",
	"653.1232", "+", "231.1234" ,"*","43.12", "/" ,"3432",	
	"// hello world this is a comment",
	"int", "double", "string"
    };

    Lexer lexer(test_string);
    auto tokens = lexer.scan_tokens();
    EXPECT_EQ(lexer.get_lexemes(), expected_lexemes);
}

// TODO: Are the exceptions given by the lexer correct?










