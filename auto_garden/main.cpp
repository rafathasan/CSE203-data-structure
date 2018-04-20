#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
    int x=10,y=10,v=10;
    int arr[x][y]={};

    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            arr[rand()%x][j%y]=rand()%v;
        }
    }

    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
}
