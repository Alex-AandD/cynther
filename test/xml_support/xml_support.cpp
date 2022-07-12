#include "pugixml.hpp"
#include "xml_support.hpp"
#include <iostream>

// this is how you load the document
//
const char* node_types[] =
{
    "null", "document", "element", 
    "pcdata", "cdata", "comment", "pi", 
    "declaration"
};

struct simple_walker: pugi::xml_tree_walker
{
    virtual bool for_each(pugi::xml_node& node)
    {
        for (int i = 0; i < depth(); ++i) std::cout << "  "; // indentation

        std::cout << node_types[node.type()] 
	    << ": name='" << node.name() 
	    << "', value='" << node.value() << "'\n";
        return true; // continue traversal
    }
};

void PrintDocument(){
    const char* filepath
    {"/Users/alexdagostino/programming/cynther/test/xml_support/tree.xml"};
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(filepath); 
    pugi::xml_node program = doc.child("program");
    simple_walker walker;
    doc.traverse(walker);
}
