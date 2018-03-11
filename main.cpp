#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include<cstring>
#include<cmath>
using namespace std;
class MyStack
{
    int top;
    char* stk;
    int size;

public:
    void allocate(int x){
        top=-1;
        stk = new char[x];
        size = x;
    }
    void push(char sym){
        if(top< size-1) stk[++top]=sym;
        else cout<<"Stack overflow!"<<endl;
    }
    char pop(){
        if(top>=0) return stk[top--];
        else {
            cout<<"Stack underflow!"<<endl;
            return '\0';
        }
    }
    bool isEmpty()
    {
        if(top >= 0) return false;
        else return true;
    }
    char topElement()
    {
       if(top>=0) return stk[top];
        else {
            cout<<"Stack underflow!"<<endl;
            return '\0';
        }
    }
};

class IntStack
{
    int top;
    int* stk;
    int size;

public:

    void allocate(int x){
        top=-1;
        stk = new int[x];
        size = x;
    }
    void push(int sym){
        if(top< size-1) stk[++top]=sym;
        else cout<<"Stack overflow!"<<endl;
    }
    int pop(){
        if(top>=0) return stk[top--];
        else {
            cout<<"Stack underflow!"<<endl;
            return -99999;
        }
    }
    bool isEmpty()
    {
        if(top >= 0) return false;
        else return true;
    }
    int topElement()
    {
       if(top>=0) return stk[top];
        else {
            cout<<"Stack underflow!"<<endl;
            return -999999;
        }
    }
};



bool isDigit(char c)
{
    if(c >= '0' && c <= '9' ) return true;
    else return false;
}

bool isOperator(char c)
{
    switch(c)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '^': return true;
        default: return false;
    }
}

int precedence(char c)
{
    switch(c)
    {
        case '(': return 0;
        case '+':
        case '-': return 1;
        case '*':
        case '/':
        case '%': return 2;
        case '^': return 3;
        default: return 0;
    }
}

class EvalOfExpression
{
    string infix, postfix="";
    MyStack charStk;
    IntStack intStk;
    int result,*digits;
public:
    void getInfix(){
        cout<<"Enter an infix Statement: "; cin>>infix;
        charStk.allocate(infix.length());
        intStk.allocate(infix.length());
    }
    void covertToPostfix()
    {
        int index=0,i; char curSym, poppedSym;
        int preceCur, preceTop;
        for(i=0; i<infix.length();i++)
        {
            curSym=infix[i];

            if(isDigit(curSym)) postfix += curSym;
            else if(curSym == '(') charStk.push(curSym);
            else if(isOperator(curSym))
            {
                preceCur = precedence(curSym);
                preceTop = precedence(charStk.topElement());
                if((preceCur == preceTop && preceTop != 3) || precedence(charStk.topElement())>precedence(curSym))
                    while( !charStk.isEmpty() && precedence(charStk.topElement())>=precedence(curSym))
                     postfix += charStk.pop();

                charStk.push(curSym);
            }
            else if(curSym == ')')
                while((poppedSym = charStk.pop()) != '(') postfix += poppedSym;
        }

        while(!charStk.isEmpty())
        {
            postfix += charStk.pop();
        }
    }

    void convertDigitToInt(){
      string di="";
      int d=0;
      for(int i=0;postfix[i]!='\0';i++){
            if(isDigit(postfix[i])){
              for(int j=i;isDigit(postfix[j]);j++,i++){
              }
              d++;
              i=i-1;
            }
        }digits = new int[d];d==0;

        for(int i=0,d=0;postfix[i]!='\0';i++){
              if(isDigit(postfix[i])){
                for(int j=i;isDigit(postfix[j]);j++,i++){
                  di+=postfix[j];
                }
                stringstream strr;
                strr<<di;
                strr>>digits[d];
                strr.clear();
                di="";
                d++;
                i=i-1;
              }
          }
          cout<<"int"<<endl;
          for(int i=0;i<d;i++)
            cout<<digits[i]<<" ";
    }

    void evaluatePostfix(){
        int i,d=0, lhop, rhop;
        for(i=0,d++;i<postfix.length();i++)
        {
            if(isDigit(postfix[i]))
            {
                for(int j=i;isDigit(postfix[j]);j++,i++){}
                intStk.push(digits[d]);
                d++;
                i=i-1;

            }
            else if(isOperator(postfix[i]))
            {
                rhop = intStk.pop();
                lhop = intStk.pop();
                switch(postfix[i])
                {
                case '+': intStk.push(lhop+rhop);break;
                case '-': intStk.push(lhop-rhop);break;
                case '*': intStk.push(lhop*rhop);break;
                case '/': intStk.push(lhop/rhop);break;
                case '%': intStk.push(lhop%rhop);break;
                case '^': intStk.push((int)pow((double)lhop,rhop));break;
                }
            }
        }
        result = intStk.pop();
    }
    void display()
    {
        cout<<"Infix = "<<infix<<endl;
        cout<<"Postfix = "<<postfix<<endl;
        cout<<"Result = "<<result<<endl;
    }
};

int main()
{
    EvalOfExpression obj;
    obj.getInfix();
    obj.covertToPostfix();
    obj.convertDigitToInt();
    obj.evaluatePostfix();
    obj.display();
    return 0;
}
