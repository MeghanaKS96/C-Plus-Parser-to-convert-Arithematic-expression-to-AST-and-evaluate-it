#include<stack>
#include<iostream>
#include "expr.h"


//Building an AST tree using Shunting Yard Algo !
ASTNode * BuildAST::build(std::string input)
{
    input="(" + input + ")";
    char c ;
    int prec[123]={0};
    prec['+']=2,prec['-']=1,prec['*']=3,prec['/']=4,prec['('] = prec[')'] = 0;
    std::stack<char> OpStack;
    char op;
    NewNodeOfMeg * e1, * e2;
    std::stack<NewNodeOfMeg*> Numstack;
    for(int i=0;i<input.length();i++)
    {
       c=input[i];
        
        
         if (c == '(')
        {
            OpStack.push(c);
        }

            else if (c == ')'){
                while (!OpStack.empty() && OpStack.top() != '(')
                {
                    op = OpStack.top();
                    OpStack.pop();
                    
                    e2 = Numstack.top();
                    Numstack.pop();
                    e1 = Numstack.top();
                    Numstack.pop();
                    Numstack.push(new NewNodeOfMeg(std::string(1,op),"", e1, e2));
                }
                if(!OpStack.empty())
                OpStack.pop();
            }

            else if (isdigit(c))
        {
            
            std::string fullval=std::string(1,c);
            for(int v=1;v<input.length();v++)
            {
                if(isdigit(input[i+v]))
                {
                    fullval=fullval+input[i+v];
                }
                else
                {
                    
                    break;
                }
            }
            Numstack.push(new NewNodeOfMeg("",fullval,NULL,NULL));
            i=i + fullval.length()-1;
            
        }
        else if (!isdigit(c))
        {
            while(!OpStack.empty() && OpStack.top()!='(' && prec[OpStack.top()] > prec[c]){
                op = OpStack.top();
                OpStack.pop();
                
                e2 = Numstack.top();
                Numstack.pop();
                e1 = Numstack.top();
                Numstack.pop();
                Numstack.push(new NewNodeOfMeg(std::string(1,op),"", e1, e2));
            }
            OpStack.push(c);
        }
        
        else if (!isdigit(OpStack.top()))
        {
            while(prec[c]<prec[OpStack.top()])
            {
              op = OpStack.top();
              OpStack.pop();
                
                e2 = Numstack.top();
                Numstack.pop();
                e1 = Numstack.top();
                Numstack.pop();
                Numstack.push(new NewNodeOfMeg(std::string(1,op),"", e1, e2));  
            }
            OpStack.push(c);
        }
    }
    while(!OpStack.empty())
    {
        op = OpStack.top();
        OpStack.pop();
                
                e2 = Numstack.top();
                Numstack.pop();
                e1 = Numstack.top();
                Numstack.pop();
                Numstack.push(new NewNodeOfMeg(std::string(1,op),"", e1, e2)); 
    }
    return Numstack.top();
}


//Str function to return the s-expr notion with paranthesis
std::string NewNodeOfMeg::str(ASTNode * root)
{
    std::string sxpr="";
    if(root->GetVal()!="")
    {
      sxpr=sxpr + root->GetVal();
    }
    else
    {
        sxpr = sxpr + "("+root->GetOp();
        sxpr= sxpr + str(root->GetLeft());
        sxpr= sxpr + str(root->GetRight());
        sxpr= sxpr+")";
    }

    return sxpr;
}

int NewNodeOfMeg::evaluate()
{
     return travel(this);
}

int NewNodeOfMeg::travel(ASTNode * r)
{
  if(r->GetVal()!="")
  {
      return stoi(r->GetVal());
  }
  else
  {
      int left_child = travel(r->GetLeft());
      int right_child = travel(r->GetRight());
      std::string op=r->GetOp();
      int res = 0;

      if(op=="+")
      {
          res=left_child + right_child;
      }
      if(op=="-")
      {
          res=left_child - right_child;
      }
      if(op=="*")
      {
          res=left_child * right_child;
      }
      if(op=="/")
      {
          res=left_child / right_child;
      }
      return res;
  }
}


