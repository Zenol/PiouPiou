#ifndef CODE_GENERATOR_HPP_
#define CODE_GENERATOR_HPP_

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>

namespace PiouC
{
    typedef std::shared_ptr<llvm::Value> PValue;

    class FloatingExprAST;
    class IntegerExprAST;
    class StringExprAST;
    class VariableExprAST;
    class VariableDeclExprAST;
    class BinaryExprAST;
    class CallExprAST;
    class PrototypeAST;
    class ExternAST;
    class FunctionAST;

    class CodeGenerator
    {
    public:
        CodeGenerator();
        ~CodeGenerator();

        PValue codegen(FloatingExprAST *expr);
        PValue codegen(IntegerExprAST *expr);
        PValue codegen(StringExprAST *expr);
        PValue codegen(VariableExprAST *expr);
        PValue codegen(VariableDeclExprAST *expr);
        PValue codegen(BinaryExprAST *expr);
        PValue codegen(CallExprAST *expr);
        PValue codegen(PrototypeAST *expr);
        PValue codegen(ExternAST *expr);
        PValue codegen(FunctionAST *expr);

    private:
        llvm::LLVMContext &context;
        llvm::Module *module;
    };
}

#endif /* !CODE_GENERATOR_HPP_ */
