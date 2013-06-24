#include "CodeGenerator.hpp"
#include "CodeGeneratorException.hpp"

#include "AST.hpp"

namespace PiouC
{

    CodeGenerator::NamedVariables&
    CodeGenerator::get_scoped_values()
    {
        return (local_scope) ? values_local : values_global;
    }

    CodeGenerator::CodeGenerator()
        :context(llvm::getGlobalContext()),
         module(new llvm::Module("JIT", context)),
         builder(context),
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
        NamedVariables &scope = get_scoped_values();

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
        using namespace llvm;
        PValue left = expr->left->accept(*this);
        PValue right = expr->right->accept(*this);

        if (left->getType()->isDoubleTy() && right->getType()->isIntegerTy(64))
        {
            //TODO Should convert right to double
        }

        if (left->getType()->isIntegerTy(64) && right->getType()->isDoubleTy())
        {
            //TODO Should convert right to double
        }

        switch (expr->op)
        {
        case Token::Affect:
        {
            NamedVariables &scope = get_scoped_values();
            //TODO
            return PValue(nullptr);
        }
        case Token::Plus:
        case Token::Minus:
        case Token::Mult:
        case Token::Div:
        case Token::Lt:
        case Token::Gt:
        case Token::Equal:
        default:
            throw CGException(CGExceptionType::UnknownBinaryOperator);
        }
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

    PAllocaInst
    CodeGenerator::create_entry_block_alloca(std::string name, Type type)
    {
        using llvm::IRBuilder;
        using llvm::AllocaInst;
        typedef llvm::Type lType;
        auto &entry_block = current_function->getEntryBlock();
        IRBuilder<> tmp_bldr(&entry_block,
                                 entry_block.begin());

        AllocaInst *alloca = nullptr;
        switch(type)
        {
        case Type::Floating:
            alloca = tmp_bldr.CreateAlloca(lType::getDoubleTy(context), 0, name);
        case Type::String:
            //TODO
        case Type::Integer:
            alloca = tmp_bldr.CreateAlloca(lType::getInt64Ty(context), 0, name);
        }
        return PAllocaInst(nullptr);
    }
}
