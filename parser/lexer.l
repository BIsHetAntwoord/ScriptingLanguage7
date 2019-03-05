%{
#include "parser/parser_info.hpp"
#include "parser/parser.parser.hh"

#include <cstring>

char* dup_str(const char* s)
{
    char* result = new char[std::strlen(s) + 1];
    char* result_ptr = result;
    while(*s)
    {
        *result_ptr++ = *s++;
    }
    *result_ptr = 0;
    return result;
}

%}

%option nounput
%option prefix="parser_yy"
%option never-interactive
%option bison-bridge
%option reentrant
%option extra-type="struct parse_info*"

BIN_DIGIT [01]
HEX_DIGIT[0-9A-Fa-f]
OCT_DIGIT [0-7]
DIGIT [0-9]
WHITESPACE [ \t\r\f\v]
NEWLINE \r?\n|\r
IDCHAR [_A-Za-z]
IDENTIFIER {IDCHAR}({IDCHAR}|{DIGIT})*

%%

<INITIAL>
{
    "try"                                                                   {return TRY;}
    "="                                                                     {return ASSIGN;}
    "+"                                                                     {return PLUS;}
    "-"                                                                     {return MIN;}
    "*"                                                                     {return MUL;}
    "/"                                                                     {return DIV;}
    "%"                                                                     {return MOD;}
    "&"                                                                     {return BITAND;}
    "|"                                                                     {return BITOR;}
    "^"                                                                     {return BITXOR;}
    "~"                                                                     {return BITNOT;}
    ";"                                                                     {return SEMICOLON;}
    "("                                                                     {return OPEN_PAR;}
    ")"                                                                     {return CLOSE_PAR;}
    "0b"{BIN_DIGIT}+                                                        {yylval->integer = std::strtoull(yytext, nullptr, 2); return INTEGER;}
    "0x"{HEX_DIGIT}+                                                        {yylval->integer = std::strtoull(yytext, nullptr, 16); return INTEGER;}
    "0"{OCT_DIGIT}+                                                         {yylval->integer = std::strtoull(yytext, nullptr, 8); return INTEGER;}
    {DIGIT}+                                                                {yylval->integer = std::strtoull(yytext, nullptr, 10); return INTEGER;}
    {IDENTIFIER}                                                            {yylval->str = dup_str(yytext); return ID;}
    {WHITESPACE}                                                            {}
    {NEWLINE}                                                               {++yyextra->line;}
    .                                                                       {return ERROR_TOKEN;}
}

%%

extern "C" int parser_yywrap(yyscan_t)
{
    return 1;
}
