#include "queue"
#include "iostream"
#include "vector"
#include "fstream"
using namespace std;
class LeafNode{
  int frequency;
  char letter;
  LeafNode*left;
  LeafNode*right;
public:
  LeafNode(){
    letter=NULL;
    frequency=0;
    left=NULL;
    right=NULL;
  }
  LeafNode*&getLeft(){
    return left;
  }
  LeafNode*&getRight(){
    return right;
  }
  int getFreq(){
    return frequency;
  }
  void setFreq(int set=0){
    frequency=set;
  }
  int getChar(){
    return letter;
  }
  void setChar(char set=0){
    letter=set;
  }
};

class HuffmanTree{
  LeafNode*root;
public:
  HuffmanTree(){
    root=NULL;
  }
  LeafNode*&getRoot(){
    return root;
  }
  void setRoot(LeafNode*&set){
    root=set;
  }
  LeafNode*&combineTree(LeafNode*&l,LeafNode*&r){
    LeafNode*temp;
    temp->getLeft()=l;
    temp->getRight()=r;
    temp->setFreq(l->getFreq()+r->getFreq());
    return temp;
  }
};

class Encoding{
  int chr[255];
  vector<LeafNode> *ascii;
  void buildascii(string file){
    string sentance;
    ifstream data(file.c_str());
    data>>sentance;
    data.close();
    for(int i=0;sentance[i]!='\0';i++){
      for(int j=0;j<=255;j++){
        if(j==sentance[i]){}

      }
    }
  }
public:
  Encoding(string file){

  }

};

int main() {
  string str="abcd";
  cout<<str<<endl;
  str=str+'e';
  cout<<str<<endl;
}
