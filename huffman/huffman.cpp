#include "iostream"
#include "fstream"
using namespace std;

class MinHeapNode{
  int freq;
  char font;
  MinHeapNode*left,*right;
public:
  MinHeapNode(){
    freq=0;
    font='\0';
    left=right=NULL;
  }
  void setLeft(MinHeapNode*&l){
    left=l;
  }
  void setRight(MinHeapNode*&r){
    right=r;
  }
  MinHeapNode*&getLeft(){
    return left;
  }
  MinHeapNode*&getRight(){
    return right;
  }
  void setMinHeapNode(int frq, char f){
    font=f;
    freq=frq;
  }
  void setFreq(int i){
    freq=i;
  }
  int getFreq(){
    return freq;
  }
  char getChar(){
    return font;
  }
};

class MinHeap{
	MinHeapNode**arr;
	int length;
    void Heapify(int idx,int len){
        int heapify=idx;
        int left=2*idx+1;
        int right=2*idx+2;
        if (left<len && arr[left]->getFreq()<arr[heapify]->getFreq())
            heapify=left;
        if (right<len && arr[right]->getFreq()<arr[heapify]->getFreq())
            heapify=right;
        if (heapify!=idx){
            swap(arr[idx],arr[heapify]);
            Heapify(heapify,len);
        }
	}
public:
	void BuildHeap(){
    for (int i=(length/2)-1;i>=0;i--) Heapify(i,length);
	}
	void setMinHeap(MinHeapNode*a[],int l){
		arr=a;
		length=l;
	}
	void print(){
		for(int i=0;i<length;i++)
			cout<<arr[i]->getChar()<<arr[i]->getFreq()<<" ";
		cout<<endl;
	}
	MinHeapNode* pop(){
		MinHeapNode *temp;
		temp=new MinHeapNode;
		temp->setMinHeapNode(arr[0]->getFreq(),arr[0]->getChar());
		swap(arr[0],arr[(length)-1]);
		length--;
		Heapify(0,length);
		return temp;
	}
  MinHeapNode*top(){
    return arr[0];
  }
	void push(MinHeapNode*&n){
		arr[length]->setMinHeapNode(n->getFreq(),n->getChar());
		length++;
		BuildHeap();
	}

  int getRootFreq(){
    return arr[0]->getFreq();
  }

	int getLength(){
	return length;
	}
};


class HuffmanEncoding{
  MinHeap*encode;
  int asc;
  MinHeapNode*ascii[255];
  string line;
public:
  HuffmanEncoding(){
    encode=new MinHeap;
    asc=255;
    for(int i=0;i<asc;i++)
      ascii[i]= new MinHeapNode;
  }
  string ReadHuffTree(MinHeapNode*root,string algo,string temp){
    if(root->getChar()=='\0'){
      algo=ReadHuffTree(root->getLeft(),algo,temp+='0');
      algo=ReadHuffTree(root->getRight(),algo,temp+='1');
    }
    if(root->getChar()!='\0'){
      algo+=root->getChar();
      algo+='\n';
    }
    return algo;
  }
  void writeAlgoToFile(string file){
    string line,temp;cout<<"afasd";
    line = ReadHuffTree(encode->top(), line,temp);
    cout<<"gere:";
    ofstream ofile(file.c_str());
    ofile<<line;
    ofile.close();
  }
  void BuildHeapNode(){
    while(encode->getLength()!=1){
      MinHeapNode *l,*r,*t;
      l=encode->pop();
      r=encode->pop();
      t= new MinHeapNode;
      t->setLeft(l);
      t->setRight(r);
      t->setMinHeapNode(l->getFreq()+r->getFreq(),'\0');
      encode->push(t);
    }
  }
  void pushNodes(){
    encode->setMinHeap(ascii,asc);
    while(encode->getRootFreq()==0){
      encode->pop();
    }
  }
  void ReadLine(){
    int a;
    for(int i=0;line[i]!='\0';i++){
      a=line[i];
      char c=a;
      cout<<"'"<<c<<"' "<<a<<endl;
      ascii[a]->setMinHeapNode(ascii[a]->getFreq()+1,c);
    }
  }
  void ReadFile(string filename){
    ifstream file(filename.c_str());
    //while(!file.eof()){
      getline(file, line);
    //}
    file.close();
    ReadLine();
  }
  void ReadAscii(){
    for(int i=0;i<asc;i++){
      cout<<i<<" "<<ascii[i]->getFreq()<<" "<<ascii[i]->getChar()<<endl;
    }
    cout<<line<<endl;
  }
  void PrintHeap(){
    encode->print();
  }
};

int main(){
  string file="text.txt",algo="algo.txt";
  HuffmanEncoding afile;
  //cin>>file;
  afile.ReadFile(file);
  afile.ReadAscii();
  afile.pushNodes();
  afile.PrintHeap();
  afile.BuildHeapNode();
  afile.PrintHeap();
  afile.writeAlgoToFile(algo);
  return 0;
}
