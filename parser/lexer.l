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

%x STR

%%

<INITIAL>
{
    "false"                                                                 {return FALSE;}
    "true"                                                                  {return TRUE;}
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
    ".."                                                                    {return CONCAT;}
    ";"                                                                     {return SEMICOLON;}
    "("                                                                     {return OPEN_PAR;}
    ")"                                                                     {return CLOSE_PAR;}
    "0b"{BIN_DIGIT}+                                                        {yylval->integer = std::strtoull(yytext, nullptr, 2); return INTEGER;}
    "0x"{HEX_DIGIT}+                                                        {yylval->integer = std::strtoull(yytext, nullptr, 16); return INTEGER;}
    "0"{OCT_DIGIT}+                                                         {yylval->integer = std::strtoull(yytext, nullptr, 8); return INTEGER;}
    {DIGIT}+                                                                {yylval->integer = std::strtoull(yytext, nullptr, 10); return INTEGER;}
    {DIGIT}+("."{DIGIT}+)?([eE]{DIGIT}+)?                                   {yylval->flt = std::strtod(yytext, nullptr); return FLOAT;}
    "\""                                                                    {yyextra->parse_str.clear(); BEGIN(STR);}
    {IDENTIFIER}                                                            {yylval->str = dup_str(yytext); return ID;}
    {WHITESPACE}                                                            {}
    {NEWLINE}                                                               {++yyextra->line;}
    .                                                                       {return ERROR_TOKEN;}
}

<STR>
{
    "\\\'"                                                                  {yyextra->parse_str += "\'";}
    "\\\""                                                                  {yyextra->parse_str += "\"";}
    "\\\\"                                                                  {yyextra->parse_str += "\\";}
    "\\a"                                                                   {yyextra->parse_str += "\a";}
    "\\b"                                                                   {yyextra->parse_str += "\b";}
    "\\f"                                                                   {yyextra->parse_str += "\f";}
    "\\n"                                                                   {yyextra->parse_str += "\n";}
    "\\r"                                                                   {yyextra->parse_str += "\r";}
    "\\t"                                                                   {yyextra->parse_str += "\t";}
    "\\v"                                                                   {yyextra->parse_str += "\v";}
    "\\"{OCT_DIGIT}+                                                        {yyextra->parse_str += char(std::strtoull(yytext + 1, nullptr, 8));}
    "\\x"{HEX_DIGIT}+                                                       {yyextra->parse_str += char(std::strtoull(yytext + 2, nullptr, 16));}
    "\""                                                                    {BEGIN(INITIAL); yylval->str = dup_str(yyextra->parse_str.c_str()); return STRING;}
    {NEWLINE}                                                               {++yyextra->line; yyextra->parse_str += yytext;}
    .                                                                       {yyextra->parse_str += yytext;}
}

%%

extern "C" int parser_yywrap(yyscan_t)
{
    return 1;
}
