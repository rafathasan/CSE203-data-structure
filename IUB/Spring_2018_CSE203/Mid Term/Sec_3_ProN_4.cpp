#include "iostream"
using namespace std;

class ListNode{
 int value, position;
 ListNode *next;
 public:
 void displayPosition(){
   cout<<position<<" ";
 }
 int getValue(){
   return value;
 }
 ListNode*& getNext(){
   return next;
 }
};
int showSearchValPosBackwardsAndReturnSumOfAllNodes(ListNode*head, int val){
  int sum=0;
  if(head!=NULL)
    sum+=showSearchValPosBackwardsAndReturnSumOfAllNodes(head->getNext(),val);
  cout<<head->getValue()<<" ";
  if(head->getValue()==val)
    return head->getValue();
  return sum;
}
int main(){
 ListNode *head=NULL, *tail=NULL;
 int searchVal;
 cout<<"Enter search value: ";
 cin>>searchVal;
 int sum = showSearchValPosBackwardsAndReturnSumOfAllNodes(head, searchVal);
 cout<<"Sum of the values of all nodes = "<<sum<<endl;
 return 0;
}
