//============================================================================
// Name        : Week12.cpp
// Author      : luis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <vector>
#include <iostream>
using namespace std;

template<class T>
class Test {
	private:
		T _val;
		static T _dval; // static so all the same data type share the same default value
	public:
		Test(){/*_val = 0;*/
			_val = _dval;
		}  // be careful how you initialize
		Test(T v) : _val(v){}
		Test(const Test& b) : _val(b._val) {}
		const T getVal()const{return _val;} //********** use const just in case _val is a pointer
		void setVal(T t);
};

template<class T> // used to  initialize any type data
T Test<T>::_dval; // default value. no matter how many times class was instantiated

template<class T> // all the objects of that data type will share the default data type val
void Test<T>::setVal(T t){
	_val = t;
}

int main() {
	/*vector<int> v;
	v.push_back(7);
	cout << v[0] << endl;
	vector<int*> v2;
	v2.push_back(new int(9));
	cout << v2[0] << " " << *v2[0] << endl;
	*v2[0] = 12;
	cout << v2[0] << " " << *v2[0] << endl;
	cout << "deleting pointer" << endl;
	delete v2[0];
	*/

	Test<int> t;
	cout << t.getVal() << endl;
	t.setVal(5);
	cout << "t value: " << t.getVal() << endl;

	Test<string> t2;
	cout << t2.getVal() << endl;
	t2.setVal("hello");
	cout << "t2 value: " <<  t2.getVal() << endl;

	Test<int*> t3;
	cout << t3.getVal() << endl;
	t3.setVal(new int(9));
	cout <<  "t3 value: " << t3.getVal() << " " << *t3.getVal() << endl;
	*t3.getVal() = 12;
	cout << t3.getVal() << " " << *t3.getVal() << endl;
	delete t3.getVal();

	return 0;
}
