#include "math.h"
#include "string"
#include "iostream"
#include "sstream"
using namespace std;

int fibo(int n){
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return(fibo(n - 1) + fibo(n - 2));
}

int rev(int num, int len)
{
    if (len == 1)
        return num;
    else
        return (((num % 10) * pow(10, len - 1)) + rev(num / 10, --len));
}

void BiIntoDec(string binary, int i){
    double decNum=0;
    if (i >= 0){
        if (binary[i] == 1)
            decNum = (decNum + pow(2, i));
        else if (binary[i] == 0)
            decNum = (decNum + 0);
        BiIntoDec(binary, i - 1);
        cout << decNum;
    }
}

void decIntoHex(int n){
    int hex=0;
    if(!n)
        return;
    else{
        hex=n%16;
        decIntoHex(n/16);
    }
    if(hex>9)
        printf("%c",'A'+(hex-10));
    else
        printf("%d",hex);
}

int product(int a, int b){
    if (b==1)
        return a;
    else
        return a + product(a, b - 1);
}

int sizeArr(string str,int c){
  if(str[c]!='\0')
    c=sizeArr(str,c+1);
  return c;
}

void reverseStr(const string& str){
    int numOfChars = str.size();

    if(numOfChars == 1)
       cout << str << endl;
    else
    {
       cout << str[numOfChars - 1];
       reverseStr(str.substr(0, numOfChars - 1));
    }
}

bool isPali(const string &str, int start, int end){
    if (start >= end)
        return true;
    if (str[start] != str[end])
        return false;
    return isPali(str, ++start, --end);
}

double seriesSum(int n){
	double value = 0;
	if(n==1)
		return n;
	else if (n%2 == 0){
		value = 1.0/n + seriesSum(n-1);
		return value;
	}
	else{
		value = 1.0/n - seriesSum(n-1);
		return value;
	}
	return value;
}
