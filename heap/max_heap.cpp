#include "iostream"
using namespace std;

class Node{
	char font;
	int freq;
public:
	void setNode(char f,int fr){
		font=f;
		freq=fr;
	}
	char getChar(){
		return font;
	}
	int getFreq(){
		return freq;
	}
};
class MinHeap{
	Node**arr;
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
	void setMinHeap(Node*a[],int l){
		arr=a;
		length=l;
	}
	void print(){
		for(int i=0;i<length;i++)
			cout<<arr[i]->getChar()<<arr[i]->getFreq()<<" ";
		cout<<endl;
	}
	Node*& pop(){
		Node *temp;
		temp=new Node;
		temp->setNode(arr[0]->getChar(),arr[0]->getFreq());
		swap(arr[0],arr[(length)-1]);
		length--;
		Heapify(0,length);
		return temp;
	}
	int push(Node*&n){
		arr[length]->setNode(n->getChar(),n->getFreq());
		length++;
		BuildHeap();
	}
	int getLength(){
	return length;
	}
};

int main(){
	Node *arr[10];
	int l=10;
	for(int i=0;i<10;i++)
        arr[i]=new Node;
	arr[0]->setNode('a',2);
	arr[1]->setNode('b',4);
	arr[2]->setNode('c',9);
	arr[3]->setNode('d',4);
	arr[4]->setNode('e',7);
	arr[5]->setNode('f',8);
	arr[6]->setNode('g',1);
	arr[7]->setNode('h',3);
	arr[8]->setNode('i',4);
	arr[9]->setNode('j',8);
	MinHeap mh;
	mh.setMinHeap(arr,l);
	mh.print();
	mh.BuildHeap();
	mh.print();
	mh.pop();
	mh.print();
	mh.push(arr[0]);
	mh.print();
	mh.pop();
	mh.print();
	mh.pop();
	mh.print();
	mh.pop();
	mh.print();
	mh.pop();
	mh.print();
	mh.pop();
	mh.print();
	mh.pop();
	mh.print();
	mh.pop();
	mh.print();
	mh.pop();
	mh.print();
	mh.pop();
	mh.print();
	mh.pop();
	mh.print();
	cout<<mh.getLength();
	return 0;
}
