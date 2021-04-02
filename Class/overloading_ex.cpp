#include <iostream>
using namespace std;

// OPTION 1: MEMBER

// OPTION 2: FRIEND
class myVector
{
public:
	myVector():
		x(0), y(0), z(0) {}
	myVector(int a, int b, int c):
		x(a), y(b), z(c) {}
	friend ostream& operator<<(ostream& os, const myVector& vec);
private:
	int x, y, z;
};

ostream& operator<<(ostream& os, const myVector& vec){
	os << vec.x << ", " << vec.y << ", " << vec.z << endl;
	return os;
}

class myVector2
{
public:
	myVector2():
		x(0), y(0), z(0) {}
	myVector2(int a, int b, int c):
		x(a), y(b), z(c) {}
	ostream& operator<<(ostream& os)
	{
		os << this->x << ", " << this->y << ", " << this->z << endl;
	return os;
	}	
private:
	int x, y, z;
};

int main()
{
	myVector v1(2,4,6);
	myVector2 v2(2,4,6);
	// cout<<v1<<endl; // gives error b/c not single value
	//option1 = friend
	operator<<(cout,v1);
	cout << v1;
	//option2 = member
	v2 << cout; // like v2.operator<<(cout)
	v2.operator<<(cout);
	// NEED to do v2.operator b/c is MEMBER

	return 0;
}