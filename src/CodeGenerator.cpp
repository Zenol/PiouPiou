#include "CodeGenerator.hpp"

#include "AST.hpp"

namespace PiouC
{

    CodeGenerator::CodeGenerator()
        :context(llvm::getGlobalContext()),
         module(new llvm::Module("JIT", context)),
         local_scope(false)
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
        using namespace llvm;
        // auto u8_type = Type::getInt8Ty(context);
        //auto array_type = ArrayType::get(u8_type,
        //                                 expr->value.size() + 1);
        //std::cout << "String";
        return PValue(nullptr);
    }

    PValue
    CodeGenerator::codegen(VariableExprAST *expr)
    {
        using namespace llvm;
        PValue var;
        if (values_global.find(expr->name) != values_global.end())
            var = values_global[expr->name];
        if (values_local.find(expr->name) != values_local.end())
            var = values_local[expr->name];
        if (!var)
        {
            std::cerr << "Warning: "
                      << "Undeclared variable '"
                      << expr->name
                      << "' typed as integer."
                      << std::endl;
            //Build a 0 signed int value
            var = PValue(ConstantInt::get(context, APInt(64, 0, true)));
        }
        return var;
    }

    PValue
    CodeGenerator::codegen(VariableDeclExprAST *expr)
    {
        using namespace llvm;
        Value *value = nullptr;
        switch(expr->type)
        {
        case Type::Floating:
            value = ConstantFP::get(context, APFloat((double)0.0));
        case Type::String:
            //TODO
        case Type::Integer:
            value = ConstantInt::get(context, APInt(64, 0, true));
        }
        NamedValues &scope = (local_scope) ? values_local : values_global;

        if (scope[expr->name])
            std::cerr << "Warning: "
                      << "Redeclaration of the variable '"
                      << expr->name
                      << "'."
                      << std::endl;
        scope[expr->name] = PValue(value);

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
