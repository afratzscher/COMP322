//COMP322 Assignment 1
// NAME: Anne-Sophie Fratzscher
//ID: 260705446

// how to compile: g++ -o a1.out assignment1.cpp
// how to run: ./a1.out

#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

const int rows = 5;
const int cols = 5;
static int runs = 0;
static int i = 0;
static int j = 0;

void checkPassword(){
	string input;
	cout<<"Please enter a password: ";
	getline(cin, input); //allows for spaces in password

	bool issue = false; // checks if all conditions met before accepting

	// check at least 8 chars
	if(input.length() < 8){
		issue = true;
		cout<<"Password must be at least 8 characters long"<<endl;
	}

	// make sure each char doesnt appear > 2 times
	int freq[256]={0}; // initialize all chars to 0
	for(int i = 0; i < input.length(); i++){
		freq[input[i]]++;
	}
	for(int i = 0; i < 256; i++){
		if (freq[i]>2){
			issue = true;
			cout<<"'"<<char(i)<<"'"<<" appears more than twice"<<endl;
		}
	}

	//check if at least 1 number
	//uses fact that 48-57 = 0-9 in ascii
	bool num_check = false;
	for (int i = 48; i < 58; i++){
		if(freq[i]>0){
			num_check = true;
			break;
		}
	}
	if (!num_check){
		issue = true;
		cout<<"Password must contain at least one number"<<endl;
	}

	//missing *, #, $
	if(!((input.find("#") != std::string::npos)
		|| (input.find("$") != std::string::npos)
		|| (input.find("*") != std::string::npos))){
		issue = true;
		cout<<"Password must contain at least one of the following special characters: *, #, $"<<endl;
	}

	//if no issues, print that password accepted
	if (!issue){
		cout<<"Your password has been accepted"<<endl;
	}
	cout<<endl;
}

void convertPhonetic(){
	//assumes only ONE word as input -> if multiple words, only first word used
	string input;
	cout<<"Please enter a word: ";
	cin>>input;
	for(int i=0; i < input.length(); i++){
		//use switch cases because more optimized than if,else
		switch(tolower(input[i])){
			case 'a':
				cout<<"Alpha";
				break;
			case 'b':
				cout<<"Bravo";
				break;
			case 'c':
				cout<<"Charlie";
				break;
			case 'd':
				cout<<"Delta";
				break;
			case 'e':	
				cout<<"Echo";
				break;
			case 'f':
				cout<<"Foxtrot";
				break;
			case 'g':
				cout<<"Gold";
				break;
			case 'h':
				cout<<"Hotel";
				break;
			case 'i':
				cout<<"India";
				break;
			case 'j':
				cout<<"Juliett";
				break;
			case 'k':
				cout<<"Kilo";
				break;
			case 'l':
				cout<<"Lima";
				break;
			case 'm':
				cout<<"Mike";
				break;
			case 'n':
				cout<<"November";
				break;
			case 'o':
				cout<<"Oscar";
				break;
			case 'p':
				cout<<"Papa";
				break;
			case 'q':
				cout<<"Quebec";
				break;
			case 'r':
				cout<<"Romeo";
				break;
			case 's':
				cout<<"Sierra";
				break;
			case 't':
				cout<<"Tango";
				break;
			case 'u':
				cout<<"Uniform";
				break;
			case 'v':
				cout<<"Victor";
				break;
			case 'w':
				cout<<"Whiskey";
				break;
			case 'x':
				cout<<"X-ray";
				break;
			case 'y':
				cout<<"Yankee";
				break;
			case 'z':
				cout<<"Zulu";
				break;
		}
		cout<<" ";
	}
	cout<<endl;
	cout<<endl;
}

void fillMatrix(int matrix[rows][cols]){
	//initialize rand 
	//runs too quickly, so need to add something accounting for # times run
	int n = 1; // TO REMOVE
	srand(time(NULL) - runs*2);
	//fill in row 0, then row 1, ...
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			// HOW TO SET RAND: rand() % (max_number + 1 - minimum_number) + minimum_number
			matrix[i][j] = (rand() % (25+1-0)+0);
		}
	}
	runs++; // increment # times run for srand
}

void printMatrix(int matrix[rows][cols]){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			cout<<matrix[i][j];
			if(j<cols-1){
				cout<<" | ";
			}
		}
		cout<<endl<<"----------------------"<<endl;
	}
	cout<<endl;
}

void multiplyMatrices(int matrix_left[rows][cols],
						int matrix_right[rows][cols],
						int matrix_result[rows][cols]){
	// set to static so that change values while in function
	// BUT, declare in function so that remove from memory after function done running
	static int row1 = 0, col1 = 0, col2 = 0;
	
	// if filled all rows of result matrix, are done
	if (row1 >= rows){ return; }

	// fill column by column 
	if (col1 < cols){
		// for each cell, get value
		if (col2 < cols){
			matrix_result[row1][col1] += matrix_left[row1][col2] * matrix_right[col2][col1];
			col2++;
			multiplyMatrices(matrix_left, matrix_right, matrix_result);
		}
		col2=0;
		col1++;
		multiplyMatrices(matrix_left, matrix_right, matrix_result);
	}

	// fill result matrix row by row
	col1=0;
	row1++;
	multiplyMatrices(matrix_left, matrix_right, matrix_result);
}

int main(){
	checkPassword();
	convertPhonetic();
	int matrix[rows][cols];
	int matrix2[rows][cols];
	int matrix_result[rows][cols] = {0};
	fillMatrix(matrix);
	fillMatrix(matrix2);
	printMatrix(matrix);
	printMatrix(matrix2);
	multiplyMatrices(matrix, matrix2, matrix_result);
	printMatrix(matrix_result);
	return 0;

}
