#ifndef CODE_GENERATOR_HPP_
#define CODE_GENERATOR_HPP_

#include "AST.hpp"

#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>

namespace PiouC
{
    class CodeGenerator
    {
    public:
        CodeGenerator();
        ~CodeGenerator();

    private:
        typedef std::shared_ptr<llvm::Module> PModule;

        llvm::LLVMContext &context;
        PModule module;
    };
}

#endif /* !CODE_GENERATOR_HPP_ */
