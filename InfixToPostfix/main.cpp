#include <iostream>
#include <fstream>
using namespace std;

class CharStack{
  char *c;
  int top,capacity;
public:
  CharStack(int length){
    capacity=length;
    c = new char[capacity];
    top =-1;
  }
  void push(char ch){
    if(!full())
      c[++top]=ch;
    else
      cout<<"stack overflow Detected"<<endl;
  }
  char pop(){
    if(!empty())
      return c[top--];
    else
      cout<<"stack underflow Detected"<<endl;
      return '\0';
  }
  char gettop(){
    if(!empty())
      return c[top];
    else
      return ' ';
  }
  bool empty(){
    if(top<0)
      return true;
    else
      return false;
  }
  bool full(){
    if(top>=capacity-1)
      return true;
    else
      return false;
  }
  int getCapacity(){
    return capacity;
  }
  void listElement(ofstream&out){
      out<<"char stack: ";
      for (int i=0;i<=top;i++) {
        out<<c[i]<<" ";
      }
      out<<endl;
  }
};

class floStack{
  float *c;
  int top,capacity;
public:
  floStack(int length){
    capacity=length;
    c = new float[capacity];
    top =-1;
  }
  void push(float in){
    if(!full())
      c[++top]=in;
    else
      cout<<"stack overflow Detected"<<endl;
  }
  float pop(){
    if(!empty())
      return c[top--];
    else
      cout<<"stack underflow Detected"<<endl;
  }
  float gettop(){
    if(!empty())
      return c[top];
    else
      return 0;
  }
  bool empty(){
    if(top<0)
      return true;
    else
      return false;
  }
  bool full(){
    if(top>=capacity-1)
      return true;
    else
      return false;
  }
  int getCapacity(){
    return capacity;
  }
  void listElement(ofstream&out){
    out<<"float stack: ";
    for (int i=0;i<=top;i++) {
      out<<c[i]<<" ";
    }
    out<<endl;
  }
};

bool digit(char c){
    if(c >= '0' && c <= '9' ) return true;
    else if(c=='.') return true;
    else return false;
}

class Operation{
  string str,strpost;
  string newfile;
  CharStack *charobj=NULL;
  floStack *flobj=NULL;
  char **digits=NULL;
  int *intdigits=NULL;
  float *opperents=NULL;
public:
  Operation(string file,string line){
      newfile=file;
      str=line;
      ofstream out(newfile.c_str());
      out<<"Infix: "<<str<<endl;
      out.close();
      createObjects(str.length());
  }

  void createObjects(int capacity){
    charobj = new CharStack(capacity);
    flobj = new floStack(capacity);
  }

  int digitCount(string str){
    int c=0;
    for(int i=0;str[i]!='\0';i++){
      if(digit(str[i])){
        for(int j=i;digit(str[j]);j++,i++){};
        c++;
      }
    }
    return c;
  }

  void infixToPostfix(){
    CharStack cobj(str.length());
    ofstream out(newfile.c_str(),ios::app);
    for(int i=0,d=0;str[i]!='\0';i++){
      if(str[i]!=' '){
          if(digit(str[i])){
            for(int j=i;digit(str[j]);j++,i++){
              strpost+=str[j];
              d++;
            }
              strpost+=" ";
            i=i-1;
          }
          else{
              if (str[i]=='(') {
                cobj.push(str[i]);
              }
              else if(str[i]==')'){
                while(cobj.gettop()!='('){
                  strpost+=cobj.pop();
                  strpost+=" ";
                }
                cobj.pop();
              }
              else if(str[i]==' '){}
              else{
                if(precedence(str[i])>precedence(cobj.gettop())){
                  cobj.push(str[i]);
                }
                else{
                  strpost+=cobj.pop();
                  strpost+=" ";
                  cobj.push(str[i]);
                }
              }
          }
        }
        cobj.listElement(out);
      }
      while(cobj.gettop()!=' '){
        strpost+=cobj.pop();
        cobj.listElement(out);
      }
      out<<"Postfix: "<<strpost<<endl;
      out.close();
    }

    void resolvePostfix(){
      if(opperents==NULL)
        charOpperentIntoIntArray();
        string pstr=strpost;
        float l,r;
        ofstream out(newfile.c_str(),ios::app);
        for(int i=0,d=0;pstr[i]!='\0';i++){
          if(pstr[i]!=' '){
              if(digit(pstr[i])){
                for(int j=i;digit(pstr[i]);j++,i++){}
                i=i-1;
                flobj->push(opperents[d]);
                d++;
                }
                else{
                  r=flobj->pop();
                  l=flobj->pop();
                  switch (pstr[i]) {
                    case '+':flobj->push(l+r);break;
                    case '-':flobj->push(l-r);break;
                    case '*':flobj->push(l*r);break;
                    case '/':flobj->push(l/r);break;
                    case '^':
                      for(int i=1;i<r;i++){
                        l*=l;
                      }
                      flobj->push(l);break;
                  }
                }
                flobj->listElement(out);
              }
            }
            out<<"Solution: "<<flobj->pop()<<endl;
            out.close();
    }

    void charOpperentIntoIntArray(){
        if(digits==NULL||intdigits==NULL)
          opperentIntoArray();
        opperents=new float[digitCount(str)];
        for(int i=0;i<digitCount(strpost);i++){
          opperents[i]=charToInt(digits,i,intdigits[i]);
        }
    }

    void opperentIntoArray(){
      int num=0,nom=0;
      for(int i=0;str[i]!='\0';i++){
          if(digit(str[i])){
            for(int j=i;digit(str[j]);j++,i++){
            }
            num++;
          }
      }digits = new char*[num];
      intdigits=new int[num];
      num=0;
      for(int i=0,d=0;str[i]!='\0';i++){
          if(digit(str[i])){
            nom=0;
            for(int j=i;digit(str[j]);j++,i++){
              nom++;
            }
            num++;
            digits[d]=new char[nom];
            intdigits[d]=nom;
            d++;
          }
      }num=0;
      for(int i=0,d=0;str[i]!='\0';i++){
          if(digit(str[i])){
            for(int j=i,e=0;digit(str[j]);j++,i++,e++){
              digits[d][e]=str[i];
            }
            d++;
          }
      }
    }

    float charToInt(char**c,int i,int j){
      float calc=0,power=1,decimal=1,decPower=1;
      for(int k=j;k>0;k--){
        if(c[i][k-1]=='.')
          decimal*=power;
        else{
          calc+=(c[i][k-1]-48)*power;
          power*=10;
        }
      }
      return calc/decimal;
    }

  int precedence(char ch){
      switch(ch)
      {
          case '(': return 0;
          case '+': return 1;
          case '-': return 1;
          case '*': return 2;
          case '/': return 2;
          case '%': return 3;
          case '^': return 4;
          default:  return 0;
      }
  }

};

bool validInfix(string line){
int parenthesis=0,di=0,oper=0;
if(!line.empty()){
  for(int i=0;line[i]!='\0';i++){
    if(digit(line[i])){
      if(di!=oper)
        return 0;
      for(int j=i,de=0;digit(line[j]);j++,i++){
        if(line[j]=='.'){
          de++;
          if(de>1)
            return 0;
        }
      }
      di++;
      --i;
    }
    else{
      switch (line[i]) {
        case '(':parenthesis++;break;
        case ')':if(!parenthesis){return 0;}else parenthesis--;break;
        case '+':oper++;break;
        case '-':oper++;break;
        case '/':oper++;break;
        case '*':oper++;break;
        case '^':oper++;break;
        default : return 0;break;
      }
    }
  }
}
  else
    return 0;
if(parenthesis!=0)
  return 0;
else if(di!=oper+1)
  return 0;
else
  return 1;
}

string readStringFromFile(string oldfile){
  string str="";
  ifstream in(oldfile.c_str());
  if(!in){
    in.close();
    return str;
  }
    getline(in, str);
  in.close();
  return str;
}

int main(){
  string oldfile="file.txt",newfile="newfile.txt";
  bool check=true;
  //cout<<"Enter a New File Name to run Operations: ";
  //cin>>newfile;
  //cout<<"Enter Existed File Name that Contain Infix Expression: ";
  //cin>>oldfile;
  if(validInfix(readStringFromFile(oldfile))){
    Operation obj(newfile,readStringFromFile(oldfile));
    obj.infixToPostfix();
    obj.resolvePostfix();
  }
  else
    cout<<"Invalid infix"<<endl;
  return 0;
}
