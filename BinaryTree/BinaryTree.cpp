#include "iostream"
using namespace std;
class Student{
  int id;
  float cgpa;
public:
  void display(){
    cout<<"ID   : "<<id<<endl;
    cout<<"CGPA : "<<cgpa<<endl;
  }
  void setID(int x){
    id=x;
  }
  void setCgpa(float x){
    cgpa=x;
  }
  int getID(){
    return id;
  }
  float getCgpa(){
    return cgpa;
  }
};

class LeafNode{
  int label;
  Student *stu;
  LeafNode *left,*right;
public:
  LeafNode(){
    left=NULL;
    right=NULL;
    stu=NULL;
  }
  void setObject(Student*&s){
    stu=s;
  }
  Student*&getObject(){
    return stu;
  }
  void setLebel(int x){
    label=x;
  }
  int getLebel(){
    return label;
  }
  LeafNode*&getLeft(){
    return left;
  }
  LeafNode*&getRight(){
    return right;
  }
};

class LinkNode{
  LinkNode *next;
  Student *s;
public:
  LinkNode(){
    next=NULL;
    s=new Student;
  }
  LinkNode*&getNext(){
    return next;
  }
  Student*&getObject(){
    return s;
  }
};

class StudentDatabase{
  LeafNode *leafRoot;
  LinkNode *linkRoot;
public:
  StudentDatabase(){
    leafRoot=NULL;
    linkRoot=NULL;
  }

  void populateStudentAndSetLeafNodeLabel(LinkNode*&newLinkNode,LeafNode*&newLeafNode){
    cout<<"ID: ";int i;cin>>i;
    newLinkNode->getObject()->setID(i);
    newLeafNode->setLebel(i);
    cout<<"CGPA: ";float c;cin>>c;
    newLinkNode->getObject()->setCgpa(c);
  }

  LeafNode*&emptyLeaf(LeafNode*&newLeafNode,int x){
  if(newLeafNode==NULL)
    return newLeafNode;
  else if(newLeafNode->getLebel()>=x)
    emptyLeaf(newLeafNode->getLeft(),x);
  else
    emptyLeaf(newLeafNode->getRight(),x);
  }

  LinkNode*&emptyLink(LinkNode*&newLinkNode){
    if(newLinkNode!=NULL)
      emptyLink(newLinkNode->getNext());
    else
      return newLinkNode;
  }

  void displayLinkNode(LinkNode*loc){
    if(loc!=NULL){
      loc->getObject()->display();
      displayLinkNode(loc->getNext());
    }
  }
  void searchByIdLeafNode(LeafNode*loc,int id){
    if(loc!=NULL){
      if(loc->getLebel()==id){
        cout<<"Found: "<<endl;
        loc->getObject()->display();
      }
      searchByIdLeafNode(loc->getLeft(),id);
      searchByIdLeafNode(loc->getRight(),id);
    }
  }
  void newEntry(){
    LeafNode *tempLeaf;
    LinkNode *tempLink;
    tempLeaf=new LeafNode;
    tempLink=new LinkNode;
    populateStudentAndSetLeafNodeLabel(tempLink,tempLeaf);
    emptyLink(linkRoot)=tempLink;
    emptyLeaf(leafRoot,tempLink->getObject()->getID())=tempLeaf;
    tempLeaf->setObject(tempLink->getObject());
  }
  void printLinkNode(){
    displayLinkNode(linkRoot);
  }
  int countIDs(LeafNode*loc,int s){
    int count=0;
    if(loc!=NULL){
      if(loc->getLebel()/100000==s){
        count++;
      }
      count+=countIDs(loc->getLeft(),s);
      count+=countIDs(loc->getRight(),s);
    }
    return count;
  }
  int countCgpa(LeafNode*loc,float s){
    int count=0;
    if(loc!=NULL){
      if(loc->getObject()->getCgpa()==s){
        count++;
      }
      count+=countIDs(loc->getLeft(),s);
      count+=countIDs(loc->getRight(),s);
    }
    return count;
  }

  void findIdsCount(){
    cout<<"Enter two Digits: ";
    int a;cin>>a;
    cout<<countIDs(leafRoot,a)<<" IDs Found."<<endl;
  }
  void findCgpaCount(){
    cout<<"Enter Cgpa to find: ";
    float a;cin>>a;
    cout<<countCgpa(leafRoot,a)<<" IDs Found."<<endl;
  }
  void SearchStudent(){
    cout<<"Enter Node Index(ID): ";int id;cin>>id;
    searchByIdLeafNode(leafRoot,id);
  }
};

int main(){
  StudentDatabase iub;
  int x=1;
  while (x) {
    cout<<"1: add a student object"<<endl;
    cout<<"2: count number of students enrolled in a year"<<endl;
    cout<<"3: finding number of students having cgpa> x"<<endl;
    cout<<"4: display student information having searchVal as id."<<endl;
    cin>>x;
    switch (x) {
      case 1:iub.newEntry();break;
      case 2:iub.findIdsCount();break;
      case 3:iub.findCgpaCount();break;
      case 4:iub.SearchStudent();break;
    }
  }
}
