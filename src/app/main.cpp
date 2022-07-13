#include "frontend/lexer.hpp"
#include "frontend/llparser.hpp"
#include "frontend/stmt.hpp"
#include <fstream>
#include <sstream>

int main(int argc, char *argv[]){
    const char* filename;
    if (argc > 1){
	filename = argv[1];
    } else {
	return 0;
    }
    std::ifstream file(filename);
    std::stringstream input_string;
    input_string << file.rdbuf();

    Lexer lexer(input_string.str());
    auto tokens = lexer.scan_tokens();
    // lexer.tokens_to_string();
    if (lexer.has_errors()){ return 1; }
    LLParser parser(tokens);
    auto final_tree = parser.parse();
    std::cout << parser.tree_to_string() << '\n';
}
