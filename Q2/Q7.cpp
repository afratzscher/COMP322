#include <iostream>

using namespace std;

class MyFactorial
{
private:
	int cNum;
public:
	MyFactorial(){}
	MyFactorial(int pNum){
		cNum = pNum;
	}	
	int factorialHelper(int x)
	{
		if(x<=1)
			return 1;
		else
			return x*factorialHelper(x-1);
	}
	void factorial(){
		if(cNum<0)
		{
			cout<<"Negative numbers not allowed"<<endl;
			return;
		}
		else
		{
			cout<<"The factorial of "<<cNum<<" is ";
			cout<<factorialHelper(cNum)<<endl;
		}
	}
};

class MyEnhancedFactorial: public MyFactorial
{
private:
	int cNum;
	int precalculated[];
public:
	MyEnhancedFactorial(int pNum) 
	{
		cNum = pNum;
		int val = 1;
		for (int i = 0; i < 6; i++)
		{
			val *= (i+1);
			precalculated[i] = val;
		}
	}
	int factorialHelper(int x)
	{
		if(x<=6)
			return 1;
		else
			return x*factorialHelper(x-1);
	}
	void factorial()
	{
		if (cNum <= 6){ // if <= 6, return precomputed
			if (cNum < 0)
			{
				cout<<"Negative numbers not allowed"<<endl;
			}
			cout<<"The factorial (from memory) of "<<cNum<<" is ";
			cout<< precalculated[cNum-1]<<endl;
		}
		else // else, get x*x-1*...*7 from factorialhelper, than multiply by 720
		{
			cout<<"The factorial of "<<cNum<<" is ";
			cout<<precalculated[6] * factorialHelper(cNum)<<endl;
		}
	}

};
int main()
{
	MyFactorial test(4);
	test.factorial();
	MyFactorial test2(-1);
	test2.factorial();
	MyEnhancedFactorial test3(4);
	test3.factorial();
	MyEnhancedFactorial test4(6);
	test4.factorial();
	MyEnhancedFactorial test5(7);
	test5.factorial();
}