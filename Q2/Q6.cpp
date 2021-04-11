#include <iostream>

using namespace std;

class MyUtility{
private:
	char* my_char_array;
public:
	MyUtility(char* a1)
	{
		this->my_char_array = a1;
	}
	char* getArray(){ // get private member
		return my_char_array;
	}
	void arrayCopy(char* &a1) 
	{
		a1 = this->my_char_array;
	}
	int getLength()
	{
		int len = 0;
		char* copy = this->my_char_array;
		// use copy, othrewise at end of my_char_array
	    while (*copy != '\0') {
	       copy++;
	        len++;
	    }
	    return len;
	}
	char* concatenate(char* a2) 
	{
		int len = 0;
		int a2len = 0;
		char* copy = a2;
	    while (*copy != '\0') {
	       copy++;
	        len++;
	        a2len++;
	    }
	    copy = this->my_char_array;
	    while (*copy != '\0') {
	    	copy++;
	        len++;
	    }

	    char *temp = new char[len+1];
	    for (int i = 0; i < len+1; i++){
	    	if (i < (len-a2len)){
	    		temp[i] = this->my_char_array[i];
	    	}
	    	else
	    	{
	    		temp[i] = a2[i-(len-a2len)];
	    	}
	    }
	    temp[len] = '\0';
	    return temp;
	}
};

int main()
{
	char a1[] = "Hello Class";
	MyUtility u(a1);
	char* a2;
	u.arrayCopy(a2);
	cout<<a2<<endl;
	cout<<"Length of a1: "<<u.getLength()<<endl;
	char a3[] = " Good luck";
	cout<<u.concatenate(a3)<<endl;
}
