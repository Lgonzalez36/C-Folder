//============================================================================
// Name        : Week10.cpp
// Author      : luis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Frac{
 private:
	long _num;
	long _den;
 public:
	Frac(long n=0, long d=1){
		_num=n;
		_den=d;
		cout << "in constructor " << _num << " " << _den << endl;
	}
	Frac operator+(Frac b) const{
		cout << this << " " << &b << endl;
		cout << "in oper+ Frac/Frac" << endl;
		return Frac(_num * b._den + _den * b._num, _den * b._den);
	}

	operator double(){
		cout << "in double type conversion operator" << endl;
		return (double) _num/_den;
	}

	long getNum() const {return _num;}
	long getDen() const {return _den;}
};

ostream& operator<< (ostream& out, const Frac& b){
	out << b.getNum() << " " << b.getDen() << endl;
}

Frac operator+(int a, Frac b ) {
	cout << "in oper+ int int/Frac" << endl;
	return Frac(a * b.getDen() + b.getNum(), b.getDen());
}

int main(){
	cout << "stmt 1: ";
	Frac f = 5;
	Frac g = 6;
	g = g + f;
	cout << "in main " << &g << " " << &f << endl;
	double d = f;
	cout << d << endl;

	cout << "stmt 2: ";
	//Frac h = f + 2;
	//cout << h << endl;
	f = 3 + g;

	return 0;
}
