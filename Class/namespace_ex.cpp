#include <iostream>
#include "quebectemp.h"
#include "floridatemp.h"
using namespace std;
using namespace QC; // use if want to only consider QC
// using namespace FL;
// NOTE: CANNOT have multiple namespaces (except if std + other)
	// in that case, will OVERRIDE -> uses MOST RECENT namespace

int main(){
	// cout<<QC::getTemp()<<endl; // to use, remove QC namespace
	// cout<<FL::getTemp()<<endl; // to use, remove QC namespace
	cout<<getTemp()<<endl; // use if define QC namespace above
}