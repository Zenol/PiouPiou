#include "CodeGenerator.hpp"

namespace PiouC
{

    CodeGenerator::CodeGenerator()
        :context(llvm::getGlobalContext()),
         module(new llvm::Module("JIT", context))
    {
    }

    CodeGenerator::~CodeGenerator()
    {}

    PValue
    CodeGenerator::codegen(FloatingExprAST *expr)
    {
        return PValue(0);
    }

    PValue
    CodeGenerator::codegen(IntegerExprAST *expr)
    {
        return PValue(0);
    }

    PValue
    CodeGenerator::codegen(StringExprAST *expr)
    {
        return PValue(0);
    }

    PValue
    CodeGenerator::codegen(VariableExprAST *expr)
    {
        return PValue(0);
    }

    PValue
    CodeGenerator::codegen(VariableDeclExprAST *expr)
    {
        return PValue(0);
    }

    PValue
    CodeGenerator::codegen(BinaryExprAST *expr)
    {
        return PValue(0);
    }

    PValue
    CodeGenerator:: codegen(CallExprAST *expr)
    {
        return PValue(0);
    }

    PValue
    CodeGenerator::codegen(PrototypeAST *expr)
    {
        return PValue(0);
    }

    PValue
    CodeGenerator::codegen(ExternAST *expr)
    {
        return PValue(0);
    }

    PValue
    CodeGenerator::codegen(FunctionAST *expr)
    {
        return PValue(0);
    }
}
