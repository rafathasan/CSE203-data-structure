#include "iostream"
using namespace std;

void print(int n){
  if(n>=1){
    cout<<n<<" ";
    print(--n);
  }
}
void pattern(int n){
  print(n);
  cout<<endl;
  if(n>=1)
    pattern(--n);
}

int main() {
 int n;
 cout<<"Enter n: ";
 cin>>n;
 pattern(n);
 return 0;
}
