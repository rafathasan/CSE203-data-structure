#include "iostream"
using namespace std;

float calcPower(int n,int p){
  if(p>1)
    n*=calcPower(n,p-1);
  else
    return n;
  return n;
}

float calcFactorial(int n){
  if(n>1)
    n*=calcFactorial(n-1);
  else
    return 1;
  return n;
}

float evalSeries(int x,int n){
  float result=0;
      result=calcPower(x,n-1)/calcFactorial(n-1);
  if(n>1)
      result+=evalSeries(x,--n);
  else
    return 1;
  return result;
}

int main() {
  int x,n;
  cout<<"Enter x: ";
  cin>>x;
  cout<<"Enter no of terms (n<=10): ";
  cin>>n;
  float result = evalSeries(x,n);
  cout<<"The result is "<<result;
  return 0;
}
