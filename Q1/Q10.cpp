#include <stdio.h>
#include<iostream>
using namespace std;

int reverse(int number){
    int reversenum = 0; // initially 0 (so first value = last value + 0)
    while (number > 0){
        reversenum = (number % 10) + (reversenum * 10);
              // e.g. 123 = (100 * 1) + (2 * 10) * (3 * 1)
        number /= 10;
    }
    return reversenum;
}

int main(){
    // assumes only positive numbers
    int input;
    cout << "Please enter a number: ";
    cin >> input;
    int reversenum = reverse(input);
    cout<<"Reverse of " << input << " is: " << reversenum;
}