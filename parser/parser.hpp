#ifndef PARSER_HPP_INCLUDED
#define PARSER_HPP_INCLUDED

#include <string>
#include <cstdio>

class TreeNode;

class Parser
{
    private:
        FILE* input;
    public:
        Parser(const std::string&);
        Parser(FILE*);
        ~Parser();

        TreeNode* parse();
};

#endif // PARSER_HPP_INCLUDED
