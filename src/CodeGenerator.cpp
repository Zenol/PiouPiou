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
        //Build a 64 bits floating number (a double)
        using namespace llvm;
        auto llvm_value = ConstantFP::get(context,
                                          APFloat(expr->value));
        return PValue(llvm_value);
    }

    PValue
    CodeGenerator::codegen(IntegerExprAST *expr)
    {
        //Build a 64 bits signet int
        using namespace llvm;
        auto llvm_value = ConstantInt::get(context,
                                           APInt(64, expr->value, true));
        return PValue(llvm_value);
    }

    PValue
    CodeGenerator::codegen(StringExprAST *expr)
    {
        //Compute a llvm u8 array
//        auto array_type = llvm::ArrayType::get(Type *ElementType,
//                                               expr->value.size() + 1);
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
