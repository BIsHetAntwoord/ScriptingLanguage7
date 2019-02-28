#ifndef PARSER_INFO_HPP_INCLUDED
#define PARSER_INFO_HPP_INCLUDED

#include <string>
#include <cstdint>

class TreeNode;

union YYSTYPE
{
    uint64_t integer;
    double flt;
    char* str;
    TreeNode* node;
};

#define PARSER_YYSTYPE_IS_DECLARED 1

struct parse_info
{
    void* scanner;
    uint64_t line;
    uint64_t errors;
    TreeNode* root;
};

extern "C" int parser_yylex(YYSTYPE*, void*);
void parser_yyset_in(FILE*, void*);
int parser_yylex_init(void**);
void parser_yyset_extra(parse_info*, void*);
void parser_yyerror(parse_info*, const char*);
int parser_yylex_destroy(void*);
int parser_yyparse(parse_info*);

#endif
