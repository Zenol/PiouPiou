#ifndef AST_HPP_
#define AST_HPP_

#include <string>
#include <vector>
#include <memory>

namespace PiouC
{

//////////////////////////////
// Base class for all nodes //
//////////////////////////////
    class ExprAST
    {
    public:
        virtual ~ExprAST()
        {};
    };

    typedef std::shared_ptr<ExprAST> PExprAST;

///////////////////////
// Node for literals //
///////////////////////
    class FloatingExprAST : public ExprAST
    {
    public:
        FloatingExprAST(float value)
            :value(value)
        {}
    private:
        float value;
    };

    class IntegerExprAST : public ExprAST
    {
    public:
        IntegerExprAST(int value)
            :value(value)
        {}
    private:
        int value;
    };

    class StringExprAST : public ExprAST
    {
    public:
        StringExprAST(const std::string &value)
            :value(value)
        {}
    private:
        std::string value;
    };

    //////////////
    // Variable //
    //////////////

    enum class Type
    {
        Floating,
        String,
        Integer,
    };

    class VariableEprAST : public ExprAST
    {
    public:
        VariableEprAST(const std::string &name, Type type)
            :name(name), type(type)
        {}
    private:
        std::string name;
        Type type;
    };

    //////////////////////
    // Binary operation //
    //////////////////////

    enum class BinOp
    {
        Floating,
        String,
        Integer,
    };

    class BinaryExprAST : public ExprAST
    {
    public:
        BinaryExprAST(BinOp op, PExprAST left, PExprAST right)
            :op(op), left(left), right(right)
        {}
    private:
        BinOp op;
        PExprAST left;
        PExprAST right;
    };

    ////////////////////////
    // Call of a function //
    ////////////////////////

    class CallExprAST : public ExprAST
    {
    public:
        CallExprAST(const std::string &name, const std::vector< PExprAST > &args)
            :name(name), args(args)
        {}
    private:
        std::string name;
        std::vector<PExprAST> args;
    };

    //////////////////////////
    // A function prototype //
    //////////////////////////

    class PrototypeAST : public ExprAST
    {
    public:
        PrototypeAST(const std::string &name, const std::vector<Type> &args)
            :name(name), args(args)
        {}
    private:
        std::string name;
        std::vector<Type> args;
    };


    class FunctionAST : public ExprAST
    {
    public:
        FunctionAST(const std::string &name, const std::vector< std::pair<std::string, Type> > &args, PExprAST imp)
            :name(name), args(args), imp(imp)
        {}
    private:
        std::string name;
        const std::vector< std::pair<std::string, Type> > args;
        PExprAST imp;
    };


}

#endif /* !AST_HPP_ */
