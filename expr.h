#include<iostream>
#include<string>


class ASTNode
{
    protected:
    std::string operation ;
    std::string val ;
    ASTNode * rightchild ;
    ASTNode * leftchild ;

    public:
    ASTNode(std::string operationl,std::string vall,ASTNode * leftl,ASTNode * rightl ){
        operation = operationl ;
        val = vall ;
        leftchild = leftl ; 
        rightchild = rightl ;
    }

    std::string GetOp()
    {
        return operation;
    } 

    std::string GetVal()
    {
        return val;
    }

    ASTNode * GetLeft()
    {
        return leftchild;
    }

    ASTNode * GetRight()
    {
        return rightchild;
    }

    virtual int evaluate() = 0 ;
    virtual std::string str(ASTNode *) = 0 ; 
    //virtual ~ASTNode()=0;

};

class NewNodeOfMeg : public ASTNode
{
    public:
    NewNodeOfMeg(std::string operation, std::string val , ASTNode * leftchild , ASTNode * rightchild):ASTNode(operation,val,leftchild,rightchild){}
    int evaluate() override ;
    std::string str(ASTNode *) override ;
    int travel(ASTNode *);

     //~NewNodeOfMeg() {} ;
};


class BuildAST
{ 
    public:
   static ASTNode * build(std::string);
};


