#include <stdio.h>
#include<iostream>
using namespace std;

bool notDivisible(int input){
    if (((input < 6) && (input > 0)) || (input < -6)){
        return true;
    }
    if ((input % 2 == 0) && (input % 3 == 0)){
        return false;
    }
    return true;
}

int main(){
    int input;
    do {
    	cout << "Please enter a number: ";
    	cin >> input;
    } while (notDivisible(input));
	
	cout << input * input << endl;
}