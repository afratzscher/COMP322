#include <iostream>
using namespace std;

int absValue(int i);
double absValue(double i);
int max(int i, int j);
int max(int i, int j, int k);

int main(){
	cout<<absValue(-4)<<endl;
	cout<<absValue(-4.3)<<endl;
	cout<<max(2,1)<<endl;
	cout<<max(2,1,10)<<endl;
}

int absValue(int i){
	// if (i > 0) return i;
	// else return -i;
	// can use ternary operator instead!
	return i>=0?i:-i;
}

// overloading with different argument type
double absValue(double i){
	// if (i > 0) return i;
	// else return -i;
	return i>=0?i:-i;
}

int max(int i, int j){
	if(i>j) return i;
	else return j;
}

// overloading with different number of arguments 
int max(int i, int j, int k){
	if((i>j)&&(i>k)) return i;
	if((j>i)&&(j>k)) return j;
	else return k;
}
