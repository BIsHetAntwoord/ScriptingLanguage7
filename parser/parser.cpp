#include "parser/parser.hpp"
#include "error/exceptions.hpp"
#include "parser/parser_info.hpp"

Parser::Parser(const std::string& filename)
{
    FILE* file = std::fopen(filename.c_str(), "rb");
    if(file == nullptr)
        throw ParseException("Failed to open file ", filename);
    this->input = file;
}

Parser::Parser(FILE* file) : input(file) {}

Parser::~Parser()
{
    std::fclose(this->input);
}

TreeNode* Parser::parse()
{
    parse_info info;
    info.errors = 0;
    info.line = 1;

    parser_yylex_init(&info.scanner);
    parser_yyset_in(this->input, info.scanner);
    parser_yyset_extra(&info, info.scanner);
    int errors = parser_yyparse(&info);
    parser_yylex_destroy(info.scanner);

    if(errors)
        return nullptr;
    else
        return info.root;
}
