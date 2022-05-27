
#include <fstream>
#include <iostream>
using namespace std;

int ctr=1;

class Test{
private:
	int x;
public:
	Test(){
		cout << ctr++  << ".  \tin constructor" << endl;
	}
	Test(const Test &t){
		cout << ctr++ << ".  " << "\tin copy constructor" << endl;
	}
	~Test(){
		cout << ctr++ << ".  " << "\tin destructor" << endl;
	}
	const Test& operator=(const Test& x){
		cout << ctr++ << ". " << "\t in operator=" << endl;
		return *this;
	}
};
Test FunctionOne(Test r){
	cout << ctr++ << ".  In FunctionOne - creating s" << endl;
	Test s;
	cout << ctr++ << ".  In FunctionOne - assigning r to s" << endl;
	s = r;
	cout << ctr++ << ".  In FunctionOne - about to return" << endl;
	return s;
}
Test FunctionTwo(Test &r){
	cout << ctr++ << ".  In FunctionTwo - creating s and assigning r to s" << endl;
	Test s = r;
	cout << ctr++ << ".  In FunctionTwo - about to return" << endl;
	return s;
}
int main(){
	cout << ctr++ << ".  In Main - creating a" << endl;
	 Test a;
	 cout << ctr++ << ".  In Main - creating b" << endl;
	 Test b;
	 cout << ctr++ << ".  In Main - calling FunctionOne" << endl;
	 b = FunctionOne(a);
	 cout << ctr++ << ".  In Main - about to end the block" << endl;

	 cout << ctr++ << ".  In Main - creating c" << endl;
	Test c;
	c = FunctionTwo(c);
	cout << ctr++ << ".  In Main - about to end program" << endl;
	return 1;
}

