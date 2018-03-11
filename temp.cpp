#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

bool digit(char c){
    if(c >= '0' && c <= '9' ) return true;
    else if(c=='.') return true;
    else return false;
}

int main(){
  string str;
  string di="";
  int *digits;
  ifstream in("file.txt");
  in>>str;
  cout<<str<<endl;
  in.close();
  int d=0;
  for(int i=0;str[i]!='\0';i++){
        if(digit(str[i])){
          for(int j=i;digit(str[j]);j++,i++){
          }
          d++;
          i=i-1;
        }
    }digits = new int[d];d==0;

    for(int i=0,d=0;str[i]!='\0';i++){
          if(digit(str[i])){
            for(int j=i;digit(str[j]);j++,i++){
              di+=str[j];
            }
            stringstream strr;
            strr<<di;
            strr>>digits[d];
            strr.clear();
            di="";
            d++;
            i=i-1;
          }
      }
      cout<<"int"<<endl;
      for(int i=0;i<d;i++)
        cout<<digits[i]<<" ";
// /////////////////////////////
// for(int i=0,d=0;str[i]!='\0';i++){
//       if(digit(str[i])){
//         for(int j=i;digit(str[j]);j++,i++){
//         }
//         integerStack.push(digits[d]);
//         d++;
//         i=i-1;
//       }
//       else{
//
//         switch (str[i]) {
//           case "":
//         }
//       }
//   }
  return 0;
}
