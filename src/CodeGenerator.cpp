#include "CodeGenerator.hpp"

#include "AST.hpp"

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
        llvm::Value *llvm_value = llvm::ConstantFP::get(context,
                                                        llvm::APFloat(expr->value));
        llvm_value->dump();
        return PValue(llvm_value);
    }

    PValue
    CodeGenerator::codegen(IntegerExprAST *expr)
    {
        return PValue(0);
    }

    PValue
    CodeGenerator::codegen(StringExprAST *expr)
    {
        std::cout << "String";
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
        expr->left->accept(*this);
        expr->right->accept(*this);
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
        for (auto inst : expr->imp)
        {
        return inst->accept(*this);
        }
        return PValue(0);
    }
}
