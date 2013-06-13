#ifndef AST_HPP_
#define AST_HPP_

#include <memory>

namespace PiouC
{

//////////////////////////////
// Base class for all nodes //
//////////////////////////////
    class ExprAST
    {
    public:
        virtual ~ExprAST() = 0;
    };

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

    enum class VarType
    {
        Floating,
        String,
        Integer,
    };

    class VariableEprAST : public ExprAST
    {
    public:
        VariableEprAST(const std::string &name, VarType type)
            :name(name), type(type)
        {}
    private:
        std::string name;
        VarType type;
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
        BinaryExprAST(BinOp op, std::shared_ptr<ExprAST*> left, std::shared_ptr<ExprAST*> right)
            :op(op), left(left), right(right)
        {}
    private:
        BinOp op;
        std::shared_ptr<ExprAST*> left;
        std::shared_ptr<ExprAST*> right;
    };

}

#endif /* !AST_HPP_ */
