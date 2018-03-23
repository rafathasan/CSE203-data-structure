#include "iostream"
#include "stdlib.h"
using namespace std;

void allocateAndDisplay(){
  int **set,*row,x,cols;
  cout<<"Enter your input: ";cin>>cols;
  set = new int*[cols];
  row = new int[cols];
  for(int i=0;i<cols;i++){
    cin>>x;
    set[i] = new int[x];
    row[i]=x;
  }
  for(int i=0;i<cols;i++){
    for(int j=0;j<row[i];j++){
      set[i][j]=(rand()%10+1)*10;
    }
  }
  for(int i=0;i<cols;i++){
    cout<<"Set-"<<i+1<<": ";
    for(int j=0;j<row[i];j++){
      cout<<set[i][j]<<" ";
    }
    cout<<endl;
  }
}

int main() {
  allocateAndDisplay();
  return 0;
}
