#include "parser/parser.hpp"
#include "intcode/treenode.hpp"
#include "intcode/intcode.hpp"
#include "error/exceptions.hpp"
#include "vm/vm.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        if(argc < 2)
        {
            std::cerr << "Usage: parser <filename>" << std::endl;
            return 1;
        }
        Parser parser(argv[1]);
        std::unique_ptr<TreeNode> synttree(parser.parse());
        if(synttree == nullptr)
            return 1;
        std::cout << "Initial syntax tree:" << std::endl;
        synttree->print(std::cout);

        compile_info info;
        std::unique_ptr<IntCode> bytecode(synttree->generate(info));

        bytecode->print(std::cout);

        VirtualMachine vm(bytecode);
        vm.execute();
    }
    catch(ParseException& e)
    {
        std::cerr << "Parser error: " << e.what() << std::endl;
    }
    return 0;
}
