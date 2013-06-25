#include "CodeGenerator.hpp"
#include "CodeGeneratorException.hpp"
#include "Exception.hpp"

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
        //Build a 64 bits signed int
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
            VariableDeclExprAST vdec(expr->name, Type::Integer);
            var = codegen(&vdec);
        }
        return var;
    }

    PValue
    CodeGenerator::codegen(VariableDeclExprAST *expr)
    {
        using namespace llvm;
        PValue value = PValue(nullptr);
        switch(expr->type)
        {
        case Type::Floating:
            value = PValue(ConstantFP::get(context, APFloat((double)0.0)));
        case Type::String:
            //TODO
        case Type::Integer:
            value = PValue(ConstantInt::get(context, APInt(64, 0, true)));
        }
        NamedVariables &scope = get_scoped_values();

        if (scope[expr->name])
            std::cerr << "Warning: "
                      << "Redeclaration of the variable '"
                      << expr->name
                      << "'. It's value will be erased."
                      << std::endl;
        else
            scope[expr->name] = create_entry_block_alloca(expr->name, expr->type);

        PValue out_value = PValue(builder.CreateStore(value.get(),
                                                      scope[expr->name].get()));

        return PValue(out_value);
    }

    PValue
    CodeGenerator::compute_int_binop(const Token op, PValue &left, PValue &right)
        throw (CGException)
    {
        using llvm::Type;
        switch(op)
        {
        case Token::Plus:
            return PValue(builder.CreateAdd(left.get(),
                                            right.get(),
                                            "tmp_iplus"));
        case Token::Minus:
            return PValue(builder.CreateSub(left.get(),
                                            right.get(),
                                            "tmp_iminus"));
        case Token::Mult:
            return PValue(builder.CreateMul(left.get(),
                                            right.get(),
                                            "tmp_fmult"));
        case Token::Div:
            return PValue(builder.CreateSDiv(left.get(),
                                             right.get(),
                                             "tmp_fdiv"));
        case Token::Lt:
        {
            PValue tmpval =  PValue(builder.CreateICmpSLT(left.get(),
                                                          right.get(),
                                                          "tmp_fcmplt"));
            return PValue(builder.CreateZExt(tmpval.get(),
                                             Type::getInt64Ty(context),
                                             "tmp_zext64"));
        }
        case Token::Gt:
        {
            PValue tmpval =  PValue(builder.CreateICmpSGT(left.get(),
                                                          right.get(),
                                                          "tmp_fcmpgt"));
            return PValue(builder.CreateZExt(tmpval.get(),
                                             Type::getInt64Ty(context),
                                             "tmp_zext64"));
        }
        case Token::Equal:
        {
            PValue tmpval =  PValue(builder.CreateICmpEQ(left.get(),
                                                         right.get(),
                                                         "tmp_fcmpeq"));
            return PValue(builder.CreateZExt(tmpval.get(),
                                             Type::getInt64Ty(context),
                                             "tmp_zext64"));
        }
        default:
            throw CGException(CGExceptionType::UnknownBinaryOperator);
        }
    }

    PValue
    CodeGenerator::compute_float_binop(const Token op, PValue &left, PValue &right)
        throw (CGException)
    {
        using llvm::Type;
        switch(op)
        {
        case Token::Plus:
            return PValue(builder.CreateFAdd(left.get(),
                                             right.get(),
                                             "tmp_fplus"));
        case Token::Minus:
            return PValue(builder.CreateFSub(left.get(),
                                             right.get(),
                                             "tmp_fminus"));
        case Token::Mult:
            return PValue(builder.CreateFMul(left.get(),
                                             right.get(),
                                             "tmp_fmult"));
        case Token::Div:
            return PValue(builder.CreateFDiv(left.get(),
                                             right.get(),
                                             "tmp_fdiv"));
        case Token::Lt:
        {
            PValue tmpval =  PValue(builder.CreateFCmpOLT(left.get(),
                                                          right.get(),
                                                          "tmp_fcmplt"));
            return PValue(builder.CreateZExt(tmpval.get(),
                                             Type::getInt64Ty(context),
                                             "tmp_zext64"));
        }
        case Token::Gt:
        {
            PValue tmpval =  PValue(builder.CreateFCmpOGT(left.get(),
                                                          right.get(),
                                                          "tmp_fcmpgt"));
            return PValue(builder.CreateZExt(tmpval.get(),
                                             Type::getInt64Ty(context),
                                             "tmp_zext64"));
        }
        case Token::Equal:
        {
            PValue tmpval =  PValue(builder.CreateFCmpOEQ(left.get(),
                                                          right.get(),
                                                          "tmp_fcmpeq"));
            return PValue(builder.CreateZExt(tmpval.get(),
                                             Type::getInt64Ty(context),
                                             "tmp_zext64"));
        }
        default:
            throw CGException(CGExceptionType::UnknownBinaryOperator);
        }
        return PValue(nullptr);
    }

    PValue
    CodeGenerator::codegen(BinaryExprAST *expr)
    {
        using namespace llvm;
        using llvm::Type;
        PValue left = expr->left->accept(*this);
        PValue right = expr->right->accept(*this);

        //Convert right to double
        if (left->getType()->isDoubleTy() && right->getType()->isIntegerTy(64))
            right = PValue(builder.CreateSIToFP(right.get(),
                                                Type::getDoubleTy(context)));

        //Convert left to double
        if (left->getType()->isIntegerTy(64) && right->getType()->isDoubleTy())
            left = PValue(builder.CreateSIToFP(left.get(),
                                               Type::getDoubleTy(context)));

        if (expr->op == Token::Affect)
        {
            auto var = std::dynamic_pointer_cast<VariableExprAST>(expr->left);
            if (!var)
                throw CGException(CGExceptionType::ExpectedVariable);
            NamedVariables &scope = get_scoped_values();

            //Convert Double to Int64
            if (right->getType()->isDoubleTy() &&
                scope[var->name]->getType()->isIntegerTy(64))
                right = PValue(builder.CreateFPToSI(right.get(),
                                                    Type::getInt64Ty(context)));

            //Convert Int64 to Double
            if (right->getType()->isIntegerTy(64) &&
                scope[var->name]->getType()->isDoubleTy())
                right = PValue (builder.CreateSIToFP(right.get(),
                                                     Type::getDoubleTy(context)));

            return PValue(builder.CreateStore(right.get(), scope[var->name].get()));
        }

        //On floats
        if (left->getType()->isDoubleTy() && right->getType()->isDoubleTy())
            return compute_float_binop(expr->op, left, right);

        //On integers
        if (left->getType()->isIntegerTy(64) && right->getType()->isIntegerTy(64))
            return compute_int_binop(expr->op, left, right);

        throw UnsupportedFeature(__FILE__ ": unsupported type for plus");
        return PValue(0);
    }

    template <typename T>
    std::vector<T*>
    vector_shared_to_vector(std::vector< std::shared_ptr<T> > v)
    {
        std::vector<T*> new_vector;

        for (auto e : v)
            new_vector.push_back(e.get());

        return new_vector;
    }

    PValue
    CodeGenerator::codegen(CallExprAST *expr)
    {
        PFunction calle = PFunction(module->getFunction(expr->name));

        if (calle->arg_size() < expr->args.size())
            throw CGExceptionType(CGExceptionType::TooFewArguments);
        if (calle->arg_size() > expr->args.size())
            throw CGExceptionType(CGExceptionType::TooMuchArguments);

        std::vector<PValue> values;
        for (auto arg : expr->args)
            values.push_back(arg->accept(*this));

        return PValue(builder.CreateCall(calle.get(),
                                         vector_shared_to_vector(values),
                                         "tmp_call"));
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
