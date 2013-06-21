#include "CodeGenerator.hpp"

namespace PiouC
{

    CodeGenerator::CodeGenerator()
        :context(llvm::getGlobalContext()),
         module(PModule(new llvm::Module("JIT", context)))
    {
    }

    CodeGenerator::~CodeGenerator()
    {}
}
