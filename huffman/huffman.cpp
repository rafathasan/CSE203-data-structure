#include "iostream"
#include "fstream"
using namespace std;
int count=0;
class Node{
    int freq;
    char font;
    Node*left;
    Node*right;
public:
    Node(){
        freq=0;font='%';
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
        length=capacity=0;
        arr=NULL;
    }
    void BuildHeap(){
        for(int i=(length/2)-1;i>=0;i--)
            Heapify(i,length);
    }
    void pop(){
        /*if(capacity==0)
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
            delete arr[length-1];
            length--;
            BuildHeap();
        }
        else{
            swap(arr[0],arr[length-1]);
            delete arr[length-1];
            length--;
            BuildHeap();
        }*/
        swap(arr[0],arr[length-1]);
        delete arr[length-1];
        length--;
        BuildHeap();
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
            cout<<"push(): new Node is empty";
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
public:
  HuffmanEncoding(){
    line={"Dwelling and speedily ignorant any steepest."};
    heap=new MinHeap;
    asc=255;
    for(int i=0;i<asc;i++)
      ascii[i]= new Node;
  }
  /*void ReadHuffTree(Node*root,string &algo,string temp){
      if(root->getChar()=='%'&&root->getLeft()!=NULL)
        ReadHuffTree(root->getLeft(),algo,temp+='0');
      if(root->getChar()=='%'&&root->getRight()!=NULL)
        ReadHuffTree(root->getRight(),algo,temp+='1');
      if(root->getChar()!='%'&&root!=NULL){
        char a=root->getChar();
        algo+=a;
        algo+=' ';
        algo+=temp;
        algo+='\n';
        cout<<algo<<endl;
        cout<<"---------------"<<endl;
        }
  }*/

  void writeAlgoToFile(string file){
    string line,temp;
    Node*tempNode=heap->top();
    //ReadHuffTree(tempNode, line,temp);
    //cout<<line;
    ofstream ofile(file.c_str());
    ofile<<line;
    ofile.close();
  }

  void flushIntoHeap(){
    for(int i=0;i<asc;i++){
      if(ascii[i]->getFreq()!=0){
        heap->push(ascii[i]);
      }
    }
  }
  void BuildHeapNode(){
    while(heap->size()!=1){
        heap->print();
        Node*left,*right,*top;
        left=heap->top();heap->pop();
        right=heap->top();heap->pop();
        top=new Node;
        top->setFreqChar(left->getFreq()+right->getFreq(),'%');
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
      getline(file, line);
    file.close();
    ReadLine();
  }
  MinHeap*&getHeap(){
  return heap;
  }
};
class HuffmanAlgorithm{
  HuffmanEncoding*en;

public:
  HuffmanAlgorithm(){
    en=new HuffmanEncoding;
  }
  void encode(string source){
    en->ReadFile(source);
    en->flushIntoHeap();
    en->BuildHeapNode();
    //en->writeAlgoToFile(algo);
  }
  void decode(string dest,string algo){

  }
};
int main(){
  string source="text.txt",dest="binary.txt",algo="HeapTree.txt";
  HuffmanAlgorithm huffman;
  int sw=0;
  while(sw!=3){
    cout<<"1. Encode: "<<endl;
    cout<<"2. Decode: "<<endl;
    cout<<"3. Exit: "<<endl;
    cin>>sw;
    if(sw==1)
      huffman.encode(source);
    else if(sw==2)
      huffman.decode(dest,algo);
  }

  return 0;
}
