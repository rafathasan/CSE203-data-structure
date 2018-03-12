class BiTree{
  int data;
  BiTree *left,*right;
public:
  BiTree(int in){
    data=in;
    left=NULL;
    right=NULL;
  }
  BiTree*&left(){
    return left;
  }
  BiTree*&right(){
    return right;
  }
};
class Node{

};
