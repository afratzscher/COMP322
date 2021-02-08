#include <iostream>
using namespace std;

int factorial(int num);
int wrappertail(int num);
int tailfact(int num, int cum);
int iterfact(int num);

int main(){
	cout<<factorial(5)<<endl; 
	cout<<wrappertail(5)<<endl;
	cout<<iterfact(5)<<endl;
	return 0;
}

// recursive factorial
int factorial(int num){
	if(num<=1)
		return 1;
	else
		return num*factorial(num-1);
}

// tail-recursive factorial
// wrapper function
int wrappertail(int num){
	return tailfact(num, 1);
}

int tailfact(int num, int cum){
	if (num == 0) return cum;
	return tailfact(num-1, num*cum);
}

// non-recursive/ iterative factorial
int iterfact(int num){
	int fact = num;
	for (int i = num-1; i>1; i--){
		fact = fact*i;
	}
	return fact;
}

