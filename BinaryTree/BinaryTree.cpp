class BiTreeNode{
  int data;
  BiTree *left,*right;
public:
  BiTreeNode(int value){
    data=value;
    left=NULL;
    right=NULL;
  }
  int getData(){
    return data;
  }
  void setLeft(BiTreeNode*tree){
    left=tree;
  }
  void setRight(BiTreeNode*tree){
    right=tree;
  }
  BiTreeNode*&left(){
    return left;
  }
  BiTreeNode*&right(){
    return right;
  }
};
class TreeNode{
  TreeNode node;
  BiTreeNode *root;
public:
  TreeNode(TreeNode*&loRoot){
    root=loRoot;
    node=NULL;
    }
  void buildNode(){
    cout<<"Enter Data(Integer): ";
    int value;cin>>value;
    if(node==NULL){
      node = new TreeNode(value);
    }
    else{
      while()
    }
  }
};
