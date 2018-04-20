/*
** Copyright (C) 2018, Rafat Hasan
** This file is part of HuffmanAlgorithmProject
** github: https://github.com/rafathasan/cpp/blob/master/huffman/huffman.cpp
**/
#include "iostream"
#include "fstream"
using namespace std;
char def='\0';
int defChar=def;
class Node{
    int freq;
    char font;
    Node*left;
    Node*right;
public:
    Node(){
        freq=0;font=def;
        left=right=NULL;
    }
    void setFreqChar(int f,char c){
    freq=f;
    font=c;
    }
    void setLeftRight(Node*l,Node*r){
        left=l;
        right=r;
    }
    int getFreq(){
    return freq;
    }
    char getChar(){
    return font;
    }
    Node*&getLeft(){
    return left;
    }
    Node*&getRight(){
    return right;
    }
};
class MinHeap{
    Node**arr;
    Node*decode;
    int length;
    int capacity;
    void Heapify(int index, int len){
        int l=index;
        int left=2*index+1;
        int right=2*index+2;
        if(left<len&&arr[left]->getFreq()<arr[l]->getFreq())
            l=left;
        if(right<len&&arr[right]->getFreq()<arr[l]->getFreq())
            l=right;
        if(l!=index){
            swap(arr[index],arr[l]);
            Heapify(l,len);
        }
    }
public:
    MinHeap(){
        decode=new Node;
        length=capacity=0;
        arr=NULL;
    }
    void BuildHeap(){
        for(int i=(length/2)-1;i>=0;i--)
            Heapify(i,length);
    }
    void pop(){
        if(capacity==0)
            cout<<"pop(): Heap is empty"<<endl;
        else if(length<capacity/2){
            Node**temp;
            temp=new Node*[capacity/2];
            for(int i=0;i<capacity/2;i++){
                temp[i]= new Node;
                if(i<length)
                    temp[i]->setFreqChar(arr[i]->getFreq(),arr[i]->getChar());
            }
            swap(arr[0],arr[length-1]);
            //delete arr[length-1];
            length--;
            BuildHeap();
        }
        else{
            swap(arr[0],arr[length-1]);
            //delete arr[length-1];
            length--;
            BuildHeap();
        }
        // swap(arr[0],arr[length-1]);
        // //delete arr[length-1];
        // length--;
        // BuildHeap();
    }
    Node*&top(){
        if(capacity==0)
            cout<<"top(): Heap is empty"<<endl;
        else{
          return arr[0];
        }
    }
    void push(Node*&newNode){
        if(newNode->getFreq()==0)
            cout<<"push(): new Node's Freq is 0";
        else if(capacity==0&&length==0){
            arr= new Node*[length+1];
            arr[length]= new Node;
            arr[0]=newNode;
            capacity++;length++;
        }
        else if(length==capacity){
            Node**temp;
            temp= new Node*[capacity*2];
            for(int i=0;i<capacity*2;i++){
                temp[i]= new Node;
                if(i<capacity)
                    temp[i]=arr[i];
                if(i==capacity)
                    temp[i]=newNode;
            }
            length++;
            capacity*=2;
            arr=temp;
        }
        else{
            arr[length]=newNode;
            length++;
        }
        BuildHeap();
    }
    bool empty(){
        return length;
    }
    int size(){
        return length;
    }
    int getRootFreq(){
        return arr[0]->getFreq();
    }
    Node*getDecodeNode(){
      return decode;
    }
    void makeHeapFromBinarySubFuction(Node*&root,string *bin,int index,char a){

      if(root==NULL)
        root=new Node;
      root->setFreqChar(1,def);
      if(bin[a][index]==48)
        makeHeapFromBinarySubFuction(root->getLeft(),bin,++index,a);
      else if(bin[a][index]==49)
        makeHeapFromBinarySubFuction(root->getRight(),bin,++index,a);
      else{
        root->setFreqChar(1,a);
      }
    }
    void makeHeapFromBinary(string bin[],char a){
       makeHeapFromBinarySubFuction(decode,bin,0,a);
       //cout<<"RECURSION is Done"<<endl;
     }
     void pushDecodedTreeintoHeap(){
       push(decode);
     }
    void print(){
      cout<<"Heap View: ";
        for(int i=0;i<length;i++)
            cout<<arr[i]->getChar()<<arr[i]->getFreq()<<" ";
        cout<<endl;
    }

};

class HuffmanEncoding{
  MinHeap*heap;
  int asc;
  Node*ascii[255];
  string line;
  string treeLine;
public:
  HuffmanEncoding(){
    line;
    heap=new MinHeap;
    asc=255;
    for(int i=0;i<asc;i++)
      ascii[i]= new Node;
  }
  void ReadHuffTree(Node*root,string &algo,string temp){
      if(root->getChar()==def&&root!=NULL)
        ReadHuffTree(root->getLeft(),algo,temp+'0');
      if(root->getChar()==def&&root!=NULL)
        ReadHuffTree(root->getRight(),algo,temp+'1');
      if(root->getChar()!=def&&root!=NULL){
          char a=root->getChar();
          algo+=a;
          algo+=' ';
          algo+=temp;
          algo+='\n';
          //cout<<algo<<endl;
          //cout<<"---------------"<<endl;
        }
  }

  void writeAlgoToFile(string file){
    string algoline,temp;
    Node*tempNode=heap->top();
    ReadHuffTree(tempNode, algoline,temp);
    cout<<algoline;
    ofstream ofile(file.c_str());
    if (ofile.is_open()){
      ofile<<algoline;
      ofile.close();
    }
    else
      cout<<"Cant open Binary Tree File !"<<endl;
    treeLine=algoline;
  }

  void flushIntoHeap(){
    for(int i=0;i<asc;i++){
      if(ascii[i]->getFreq()!=0){
        heap->push(ascii[i]);
        cout<<ascii[i]->getChar()<<ascii[i]->getFreq()<<" ";
      }
    }cout<<endl;
  }
  void BuildHeapNode(){
    cout<<"----------------------------"<<endl;
    while(heap->size()!=1){
        heap->print();
        Node*left,*right,*top;
        left=heap->top();heap->pop();
        right=heap->top();heap->pop();
        top=new Node;
        top->setFreqChar(left->getFreq()+right->getFreq(),def);
        top->setLeftRight(left,right);
        heap->push(top);
    }
  }
  void ReadLine(){
    int a;
    for(int i=0;line[i]!='\0';i++){
      a=line[i];
      char c=a;
      ascii[a]->setFreqChar(ascii[a]->getFreq()+1,c);
    }
  }
  void ReadFile(string filename){
    ifstream file(filename.c_str());
    if (file.is_open()){
      getline(file, line);
      file.close();
    }
    else
      cout<<"Cant Open Context File !"<<endl;
    ReadLine();
  }
  MinHeap*&getHeap(){
  return heap;
  }
  string getTree(){
    return treeLine;
  }
  string getData(){
    return line;
  }
  void setString(string usr){
  line=usr;
}
};

class HuffmanDecoding{
    MinHeap*heap;
  public:
    HuffmanDecoding(){
      heap=new MinHeap;
    }
    void makeTreeFromMetaTree(string *decodeTree){
      string temp;
      for(int i=0;i<255;i++){
        if(decodeTree[i][0]!='0'&&decodeTree[i][0]!='1'){
          //cout<<i<<" NULL"<<endl;
        }
        else{
          //cout<<i<<" FULL"<<endl;
          heap->makeHeapFromBinary(decodeTree, i);
        }
      }
      heap->pushDecodedTreeintoHeap();
      cout<<"--------------------------------------------------------"<<endl;
      heap->print();
      //cout<<"Manual Test: ";
      //cout<<heap->getDecodeNode()->getLeft()->getLeft()->getChar()<<endl;
    }

    void retriveFileFromBin(string retriveOrginal,string bin){

      string temp,decodedtext,temp2;
      ifstream ifile(bin.c_str());
      if (ifile.is_open()){
        ifile>>temp;
        ifile.close();
      }
      else
        cout<<"Cant Open Binary File !"<<endl;
      cout<<"binary: "<<temp<<endl;
      Node*root=heap->getDecodeNode();

      for(int i=0;;i++){
        if(root->getChar()==defChar){
          if(temp[i]==48)
            root=root->getLeft();
          else if(temp[i]==49)
            root=root->getRight();
          else
            break;
        }
        else{
          //cout<<"I went here"<<endl;
          decodedtext+=root->getChar();
          root=heap->getDecodeNode();
          --i;
        }
      }

      cout<<"decoded text :"<<decodedtext<<endl;
      ofstream ofile(retriveOrginal.c_str());
      if (ofile.is_open()){
        ofile<<decodedtext;
        ofile.close();
      }
      else
        cout<<"Cant Open Decoded File !"<<endl;
    }
};

class HuffmanAlgorithm{
  HuffmanEncoding*en;
  HuffmanDecoding*de;
  string binaryTree;
  string bin[255];
  string decodeBin[255];
  void initializeTree(){
    binaryTree=en->getTree();
  }
public:
  HuffmanAlgorithm(){
    en=new HuffmanEncoding;
    de=new HuffmanDecoding;
  }
  void encode(string source,string algo,string dest,bool fastMode){
    if(fastMode){
      string temp;
      cout<<"Enter String To Encode: ";
      cin.ignore();
      getline(cin,temp);
      en->setString(temp);
      en->ReadLine();
    }
    else{
      en->ReadFile(source);
    }
    en->flushIntoHeap();
    en->BuildHeapNode();
    en->writeAlgoToFile(algo);
  }

  void decode(string algo,string retriveOrginal,string dest){
    string temp;char a,b;int ii;
    ifstream data(algo.c_str());
    if (data.is_open()){
      while(!data.eof()){
        string patch;
        getline(data,temp);
        temp+='\n';
        a=temp[0];ii=a;
        for(int i=2;temp[i]!='\n';i++){
          b=temp[i];
          patch+=b;
        }
        if(a!='\n')
          decodeBin[ii]+=patch;
      }
    }
    else
      cout<<"Cant open Binary Tree File !"<<endl;
    data.close();
     // for(int i=0;i<255;i++)
     //   cout<<i<<" "<<decodeBin[i]<<endl;
    de->makeTreeFromMetaTree(decodeBin);
    de->retriveFileFromBin(retriveOrginal,dest);
  }
  void createBinnaryTree(){
    initializeTree();
    bool a=0,b=0;int ascIdx;
    for(int i=0;binaryTree[i]!='\0';i++){
      //cout<<" "<<i<<" "<<endl;
      if(binaryTree[i]=='\n'){
        b=0;
      }
      if(b){
        bin[ascIdx]+=binaryTree[i];
      }
      if(!a){
        if(binaryTree[i]>=0&&binaryTree[i]<=255){
          ascIdx=binaryTree[i];a=1;
        }
      }
      if(a&&binaryTree[i]==' '){
        b=1;
      }
      if(binaryTree[i]=='\n'){
        a=0;
      }
    }
    // for(int i=0;i<255;i++){
    //   cout<<bin[i]<<endl;
    //}
  }
  void BinaryFileBugPatch(string dest){ //' ' bug fixed with this function
    string str,temp;
    ifstream file(dest.c_str());
    if (file.is_open()){
      getline(file,str);
      file.close();
    }
    else
      cout<<"Cant open new binary file !"<<endl;
    for(int i=0;str[i]!='\0';i++){
      if(str[i]!=' ')
        temp+=str[i];
    }
    ofstream ofile(dest.c_str());
    if (ofile.is_open()){
      ofile<<temp;
      ofile.close();
    }
    else
      cout<<"Cant open new binary file !"<<endl;
  }

  void createBinaryFile(string dest){
    string temp=en->getData();
    int a;
    cout<<"String: "<<temp<<endl;
    ofstream destFile(dest.c_str());
    for(int i=0;temp[i]!='\0';i++){
      a=temp[i];
      destFile<<bin[a];
    }
    destFile.close();
    BinaryFileBugPatch(dest);
  }
};

int main(){
  string source="text.txt",dest="binary.txt",algo="HeapTree.txt",retriveOrginal="newfile.txt";
  HuffmanAlgorithm huffman;
  int sw=0;bool fastMode=0;
  while(sw!=4){
    cout<<"1. Encode (Includes File: Tree File, Binary File, Context File): "<<endl;
    cout<<"2. Decode (Includes File: Tree File, Binary File, Newly Created File): "<<endl;
    cout<<"3. Fast Mode With Default File Names & Manual String Input: "<<endl;
    cout<<"4. Exit: "<<endl;
    cin>>sw;
    if(sw==1){
      if(!fastMode){
        cout<<"Enter new Binary Tree File Name: ";cin>>algo;
        cout<<"Enter new Binary File Name: ";cin>>dest;
        cout<<"Enter Context File Name: ";cin>>source;
      }
      huffman.encode(source,algo,dest,fastMode);
      huffman.createBinnaryTree();
      huffman.createBinaryFile(dest);
    }
    else if(sw==2){
      if(!fastMode){
        cout<<"Enter Binary Tree File: ";cin>>algo;
        cout<<"Enter Binary File: ";cin>>dest;
        cout<<"Enter new File Name: ";cin>>retriveOrginal;
      }
      huffman.decode(algo,retriveOrginal,dest);
    }
    else if(sw==3){
        if(fastMode){
            fastMode=0;
            cout<<"Fast Mode Check: False"<<endl;
        }
        else{
            fastMode=1;
            cout<<"Fast Mode Check: True"<<endl;
            cout<<"Default File Names Set"<<endl;
            cout<<"----------------------------------"<<endl;
            cout<<"source file: text.txt "<<endl;
            cout<<"Destination File: binary.txt"<<endl;
            cout<<"Binary Tree File: HeapTree.txt"<<endl;
            cout<<"New Decoded File: newfile.txt"<<endl;
            cout<<"----------------------------------"<<endl;
        }
    }
  }

  return 0;
}
