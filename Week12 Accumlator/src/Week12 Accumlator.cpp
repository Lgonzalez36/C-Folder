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
class Accumulator {
	private:
		T _val;
		static T _dval;
	public:
		Accumulator(){_val = _dval;}
		Accumulator(T v) : _val(v){}
		T GetVal(){return _val;}
		void AddVal(const T& t){_val += t;}
};

template<class T>
T Accumulator<T>::_dval;

int main() {
	Accumulator<int> x;
	x.AddVal(7);
	cout << x.GetVal() << endl;
	x.AddVal(8);
	cout << x.GetVal() << endl;

	Accumulator<string> y;
	y.AddVal("apple");
	cout << y.GetVal() << endl;
	y.AddVal("pear");
	cout << y.GetVal() << endl;


	return 0;
}
