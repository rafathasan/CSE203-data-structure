#include "iostream"
using namespace std;

class DoublyListNode {
 int value;
 DoublyListNode *prev, *next;
 public:
 void displayValue(){
   cout<<value<<" ";
 }
 int getValue(){
   return value;
 }
 int setValue(int x){
   value=x;
 }
 DoublyListNode*& getPrev(){
   return prev;
 }
 DoublyListNode*& getNext(){
   return next;
 }
};
void InsertBeforeAndDeleteAfterNodesWithSearchVal(DoublyListNode*&head,DoublyListNode*&tail,int val){
  DoublyListNode*loc=head;
  while(loc!=NULL){
    if(loc->getValue()==val){
      loc->getNext()->setValue(loc->getValue());
      cout<<"Enter Integer: ";int temp;cin>>temp;
      loc->setValue(temp);
    }
    loc=loc->getNext();
  }
}
int main(){
 DoublyListNode *head=NULL, *tail=NULL;
 int searchVal;
 cout<<"Enter search value: ";
 cin>>searchVal;
 InsertBeforeAndDeleteAfterNodesWithSearchVal(head, tail, searchVal);
 return 0;
}
