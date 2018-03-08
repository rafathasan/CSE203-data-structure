/**
*author @rafathasankhan
*
*/
#include <iostream>
#include <math.h>

using namespace std;

class RegularPolygon{
    int noOfEdges;
    float area, perimeter, lengthOfEdges;
public:
    RegularPolygon(){
        noOfEdges=3;
        area=0;
        perimeter=0;
        lengthOfEdges=1;
    }
    void populate(){
        do{
                cout<<"No Of Edges: ";cin>>noOfEdges;
                if(noOfEdges<3)
                    cout<<"No Of Edges Can't Be less than Three!"<<endl;
                if(noOfEdges>9999)
                    cout<<"No Of Edges is limited to 9999"<<endl;
        }while(noOfEdges<3||noOfEdges>9999);
        do{
            cout<<"Length Of Edges: ";cin>>lengthOfEdges;
            if(lengthOfEdges<=0)
                cout<<"Length can't be Less than zero!"<<endl;
        }while(lengthOfEdges<=0);
    }
    void getName(){
    string name1[10]={"","hena-", "di-", "tri-", "tetra-", "penta-", "hexa-", "hepta-", "octa-", "ennea-"};
    string name2[10]={"","deca-", "icosa-", "triaconta-", "tetraconta-", "pentaconta-", "hexaconta-", "heptaconta-", "octaconta-", "enneaconta-"};
    string name3[10]={"","hecto-","dihecta-","trihecta-","tetrahecta-","pentahecta-","hexahecta-","heptahecta-","octahecta-","enneahecta-"};
    string name4[10]={"","chilia-","dischilia-","trischilia-","tetrakischilia-","pentakischilia-","hexakischilia-","heptakischilia-","octakischilia-","enakischilia-"};
    cout<<"Polygon:     "
    <<name1[noOfEdges%10]
    <<name2[(noOfEdges%100)/10]
    <<name3[(noOfEdges%1000)/100]
    <<name4[(noOfEdges%10000)/1000]
    <<"gon"<<endl;
    }
    void retrieve(){
        getName();
        cout<<"Edges Count: "<<noOfEdges<<endl;
        cout<<"Edges Length:"<<lengthOfEdges<<endl;
        if(area==0){
            calc();
            cout<<"perimeter:   "<<perimeter<<endl;
            cout<<"Area:        "<<area<<endl;
        }
        else{
            cout<<"perimeter:   "<<perimeter<<endl;
            cout<<"Area:        "<<area<<endl;
        }
        cout<<"---------------------"<<endl;
    }
    void calc(){
        float a,l,p;int theta;
            p=noOfEdges*lengthOfEdges;
            perimeter=p;
            theta=360/(noOfEdges*2);
            l=lengthOfEdges;
            l/=2;
            a=l/tan(theta*M_PI/180);
            area=a*p/2;
    }
    float retriveArea(){
        if(area==0)
            calc();
        return area;
    }
    float retriveperimeter(){
        if(perimeter==0)
            calc();
        return perimeter;
    }
    int retrieveEdges(){
        return noOfEdges;
    }

};

class DllNode{
    DllNode *head,*tail;
    RegularPolygon obj;
public:
    RegularPolygon& data(){
        return obj;
    }
    DllNode*& nextNode(){
        return tail;
    }
    DllNode*& prevNode(){
        return head;
    }
};

void addNodeAtBeginning(DllNode*& head, DllNode*& tail){
    if(head==NULL){
        head = new DllNode;
        head->nextNode()=NULL;
        head->prevNode()=NULL;
        tail=head;
        head->data().populate();
    }
    else{
        head->prevNode() = new DllNode;
        head->prevNode()->nextNode()=head;
        head=head->prevNode();
        head->prevNode()=NULL;
        head->data().populate();
    }
}

void addNodeAtEnd(DllNode*& head, DllNode*& tail){
    if(head==NULL){
        head = new DllNode;
        head->nextNode()=NULL;
        head->prevNode()=NULL;
        tail=head;
        head->data().populate();
    }
    else{
        tail->nextNode()= new DllNode;
        tail->nextNode()->prevNode()=tail;
        tail=tail->nextNode();
        tail->nextNode()=NULL;
        tail->data().populate();
    }
}

void addNodeAtNth(DllNode*& head, DllNode*& tail){
        int index;

        cout<<"n-th: ";cin>>index;
        DllNode *activeNode=head;
        int countNode=0;
        while(countNode!=index&&activeNode!=NULL){
            activeNode=activeNode->nextNode();
            countNode++;
        }
        if(index<1||index>countNode||activeNode==NULL)
            cout<<"Unable to add as "<<index<<"-th Node."<<endl;
        else if(index==countNode)
            addNodeAtEnd(head,tail);
        else if(index==1)
            addNodeAtBeginning(head,tail);
        else{
                activeNode->prevNode()->nextNode()=new DllNode;
                activeNode->prevNode()->nextNode()->prevNode()=activeNode->prevNode();
                activeNode->prevNode()->nextNode()->nextNode()=activeNode;
                activeNode=activeNode->prevNode()->nextNode();
                activeNode->nextNode()=activeNode;
                activeNode->data().populate();
        }
}

void delNodeAtBeginning(DllNode*& head,DllNode*& tail){
    if(head==NULL)
        cout<<"Unable to Find any Node"<<endl;
    else{
        if(head->nextNode()!=NULL){
            head=head->nextNode();
            delete head->prevNode();
            head->prevNode() = NULL;
        }
        else{
            delete head;
            head = tail = NULL;
        }
    }
}

void delNodeAtEnd(DllNode*& head,DllNode*& tail){
    if(tail==NULL)
        cout<<"Unable to Find any Node"<<endl;
    else{
        if(tail->prevNode()!=NULL){
            tail=tail->prevNode();
            delete tail->nextNode();
            tail->nextNode() = NULL;
        }
        else{
            delete tail;
            head = tail = NULL;
        }
    }
}

void delNodeAtNth(DllNode*& head, DllNode*& tail){
    if(head==NULL){
        cout<<"Unable to Find any Node"<<endl;
        return;
    }
    else{
        int index;
        cout<<"n-th: ";cin>>index;
        DllNode *activeNode=head;
        int countNode=0;
        while(index!=countNode&&activeNode!=NULL){
            activeNode=activeNode->nextNode();
            countNode++;
        }
        if(countNode<index||index<1){
            cout<<"Unable to Find "<<index<<"-th Node."<<endl;
        }
        else if(index==1)
            delNodeAtBeginning(head,tail);
        else if(countNode==index)
            delNodeAtEnd(head,tail);
        else{
            activeNode=activeNode->prevNode();
            activeNode->nextNode()=activeNode->nextNode()->nextNode();
            delete activeNode->nextNode()->nextNode()->prevNode();
            activeNode->nextNode()->prevNode()=activeNode;
        }

    }
}

float retriveArea(DllNode* activeNode){



    if(activeNode==NULL){
        cout<<"Unable to Find any Node"<<endl;
        return 0;
    }
    else{
        float area=0;
        while(activeNode!=NULL){
            area+=activeNode->data().retriveArea();
            activeNode=activeNode->nextNode();
        }
        return area;
    }
}

void searchAndRetriveArea(DllNode* activeNode){
    if(activeNode==NULL)
        cout<<"Unable to Find any Node"<<endl;
    else{
        float from,to;
        cout<<"Area Range to Search From : ";
        cin>>from;cout<<" to ";cin>>to;
        while(activeNode!=NULL){
            if(activeNode->data().retriveArea()>from&&activeNode->data().retriveArea()<to)
                    activeNode->data().retrieve();
            activeNode=activeNode->nextNode();
        }
    }
}

void searchAndRetriveperimeter(DllNode* activeNode){
    if(activeNode==NULL)
        cout<<"Unable to Find any Node"<<endl;
    else{
        int perimeter;
        cout<<"Perimeter to Search: ";cin>>perimeter;
        while(activeNode!=NULL){
            if(activeNode->data().retriveperimeter()==perimeter)
                activeNode->data().retrieve();
            activeNode=activeNode->nextNode();
        }
    }
}

float retriveAvgArea(DllNode* activeNode){
    if(activeNode==NULL){
        cout<<"Unable to Find any Node"<<endl;
        return 0;
    }
    else{
        float avgarea=0,c=0;
        while(activeNode!=NULL){
            avgarea+=activeNode->data().retriveArea();
            activeNode=activeNode->nextNode();
            c++;
        }
        return avgarea/c;
    }
}

float retriveAvgperimeter(DllNode* activeNode){
    if(activeNode==NULL){
        cout<<"Unable to Find any Node"<<endl;
        return 0;
    }
    else{
        float avgperimeter=0,c=0;
        while(activeNode!=NULL){
            avgperimeter+=activeNode->data().retriveperimeter();
            activeNode=activeNode->nextNode();
            c++;
        }
        return avgperimeter/c;
    }
}

void sortNode(DllNode*&head){
    DllNode*temp;
    for(DllNode*i=head;i->nextNode()!=NULL;i=i->nextNode()){
            temp=i;
        for(DllNode*j=i->nextNode();j!=NULL;j=j->nextNode()){
            if(i->data().retriveArea()<j->data().retriveArea())
                temp=j;
            else if(i->data().retriveArea()==j->data().retriveArea())
            {
                if(i->data().retriveperimeter()<j->data().retriveperimeter())
                    temp=j;
            }
        }
        DllNode*swapTemp= new DllNode;
        swapTemp->data()=temp->data();
        temp->data()=i->data();
        i->data()=swapTemp->data();
        delete swapTemp;
    }
}

void retriveNode(DllNode* activeNode){
    if(activeNode==NULL){
        cout<<"0 Node Found"<<endl;
        return;
    }
    else{
        if(activeNode->prevNode()==NULL){
            while(activeNode!=NULL){
                activeNode->data().retrieve();
                activeNode=activeNode->nextNode();
            }
        }
        else{
            while(activeNode!=NULL){
                activeNode->data().retrieve();
                activeNode=activeNode->prevNode();

            }
        }
    }
}

int main(){
    DllNode *head=NULL,*tail=NULL;
    int in;
    while(in!=-1){
            cout<<"-------------------------------------------------------------"<<endl;
            cout<<"1.  insert a node at the beginning of the list"<<endl;
            cout<<"2.  insert a node at the end of the list"<<endl;
            cout<<"3.  insert a node as the n-th node of the list"<<endl;
            cout<<"4.  delete a node from the beginning of the list"<<endl;
            cout<<"5.  delete a node from the end of the list"<<endl;
            cout<<"6.  delete the n-th node from the list"<<endl;
            cout<<"7.  return total areas of ALL of the polygons"<<endl;
            cout<<"8.  search polygons having specific area and display"<<endl;
            cout<<"9.  search polygons having specific perimeter and display"<<endl;
            cout<<"10. return average area of the polygons"<<endl;
            cout<<"11. return average perimeter of the polygons"<<endl;
            cout<<"12. SORT the linked list nodes based on areas then by no of edges"<<endl;
            cout<<"13. display the polygons in forward sequence from the list"<<endl;
            cout<<"14. display the polygons in backward sequence from the list"<<endl;
            cout<<"-------------------------------------------------------------"<<endl;
            cin>>in;
            cout<<"-------------------------------------------------------------"<<endl;
        switch(in){
            case 1:addNodeAtBeginning(head, tail);break;
            case 2:addNodeAtEnd(head, tail);break;
            case 3:addNodeAtNth(head,tail);break;
            case 4:delNodeAtBeginning(head, tail);break;
            case 5:delNodeAtEnd(head,tail);break;
            case 6:delNodeAtNth(head,tail);break;
            case 7:cout<<"Total Area: "<<retriveArea(head)<<endl;cout<<"-------------------------------------------------------------"<<endl;break;
            case 8:searchAndRetriveArea(head);break;
            case 9:searchAndRetriveperimeter(head);break;
            case 10:cout<<"Total Average Area: "<<retriveAvgArea(head)<<endl;cout<<"-------------------------------------------------------------"<<endl;break;
            case 11:cout<<"Total Average Perimeter: "<<retriveAvgperimeter(head)<<endl;cout<<"-------------------------------------------------------------"<<endl;break;
            case 12:sortNode(head);break;
            case 13:retriveNode(head);break;
            case 14:retriveNode(tail);break;
        }
    }
    return 0;
}
