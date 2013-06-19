#ifndef AST_HPP_
#define AST_HPP_

#include <string>
#include <vector>
#include <list>
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

    class VariableExprAST : public ExprAST
    {
    public:
        VariableExprAST(const std::string &name)
            :name(name)
        {}
    private:
        std::string name;
    };

    class VariableDeclExprAST : public ExprAST
    {
    public:
        VariableDeclExprAST(const std::string &name, Type type)
            :name(name), type(type)
        {}
    private:
        std::string name;
        Type type;
    };

    //////////////////////
    // Binary operation //
    //////////////////////

    class BinaryExprAST : public ExprAST
    {
    public:
        BinaryExprAST(Token op, PExprAST left, PExprAST right)
            :op(op), left(left), right(right)
        {}
    private:
        Token op;
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

    typedef std::pair<Type, std::string> ArgPair;
    typedef std::vector< ArgPair > ArgList;

    class PrototypeAST : public ExprAST
    {
    public:
        PrototypeAST(Type return_type,
                     const std::string &name,
                     const ArgList &args)
            :return_type(return_type), name(name), args(args)
        {}
    private:
        Type return_type;
        std::string name;
        ArgList args;
    };

    typedef std::shared_ptr<PrototypeAST> PPrototypeAST;


    ///////////////////////////
    // An extern declaration //
    ///////////////////////////

    class ExternAST : public ExprAST
    {
    public:
        ExternAST(std::string extern_name, PPrototypeAST prototype)
            :extern_name(extern_name), prototype(prototype)
        {}
    private:
        std::string extern_name;
        PPrototypeAST prototype;
    };

    typedef std::shared_ptr<PrototypeAST> PPrototypeAST;

    ///////////////////////////////
    // A function implementation //
    ///////////////////////////////

    typedef std::list<PExprAST> InstList;

    class FunctionAST : public ExprAST
    {
    public:
        FunctionAST(PPrototypeAST prototype, InstList imp)
            :prototype(prototype), imp(imp)
        {}
    private:
        PPrototypeAST prototype;
        InstList imp;
    };


}

#endif /* !AST_HPP_ */
