#include <stdio.h>
#include<iostream>
using namespace std;

void printNumbers(int number){
    if (number < 1){
        return;
    }
    printNumbers(number - 1);
    cout << number << " ";
}

int main(){
    int input;
    cout << "Please enter a number: ";
	cin >> input;
    printNumbers(input);
}