#ifndef CODE_GENERATOR_HPP_
#define CODE_GENERATOR_HPP_

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>

#include "CodeGeneratorException.hpp"

namespace PiouC
{
    typedef std::shared_ptr<llvm::Value> PValue;
    typedef std::shared_ptr<llvm::Function> PFunction;
    typedef std::shared_ptr<llvm::AllocaInst> PAllocaInst;

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

    enum class Type;
    enum class Token;

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
        typedef std::map<std::string, PValue> NamedVariables;

        llvm::LLVMContext &context;
        llvm::Module *module;
        llvm::IRBuilder<> builder;

        bool local_scope;
        NamedVariables values_local;
        NamedVariables values_global;

        PFunction current_function;

        //Return the current symbol list
        NamedVariables &get_scoped_values();

        //! \brief Create an \a llvm::AllocaInst
        //!
        //! Create an \a llvm::AllocaInst stored int the entry block of
        //! \a current_function.
        //!
        //! \param name Variable name
        //! \param type Variable type
        //! \return A null ptr if current_function is null.
        //!         A \a PAllocaInst otherwise.
        PAllocaInst create_entry_block_alloca(std::string name, Type type);

        //! \brief compute binop operations that return a value from two
        //!        floating operands.
        PValue compute_float_binop(const Token op, PValue &left, PValue &right)
            throw(CGException);

        //! \brief compute binop operations that return a value from two
        //!        integer operands.
        PValue compute_int_binop(const Token op, PValue &left, PValue &right)
            throw (CGException);
    };
}

#endif /* !CODE_GENERATOR_HPP_ */
