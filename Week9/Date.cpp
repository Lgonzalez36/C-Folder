#include <iostream>
#include <cstring>
using namespace std;

class Date{
private:
	int _m, _d, _y;
	void convert(string s){
	char x[5];
	x[0] = s[0];   x[1] = s[1];  x[2] = '\0';
	_m = atoi(x);
	x[0] = s[3];   x[1] = s[4];  x[2] = '\0';
	_d = atoi(x);
	x[0] = s[6];   x[1] = s[7];  x[2] = s[8];
	x[3] = s[9];   x[4] = '\0';
	_y = atoi(x);
	}
	string convert2(){
	string tm = "", td = "", ty = "";
	// char t[10];
	if (_m <= 9)
	tm = tm + "0" + to_string(_m);
	else
	tm = to_string(_m);
	if (_d <= 9)
	td = td + "0" + to_string(_d);
	else
	td = to_string(_d);
	ty = to_string(_y);
	return tm + "/" + td + "/" + ty;
	}
	char* convert3(){
	string t = convert2();
	char* c = new char[t.length()+1];
	strcpy(c, t.c_str());
	return c;
	}
public:
	Date():_m(1), _d(1), _y(2020){cout << "in default constructor" << endl;}
	Date(int m, int d, int y){
	cout << "in 3-arg constructor" << endl;
	_m = m;
	_d = d;
	_y = y;
	}
	Date(string s){
	cout << "in string type conversion function" << endl;
	convert(s);
	}

	int getM()const {return _m;}
	int getD()const {return _d;}
	int getY()const {return _y;}
	void setD(int x) {_d = x;}
	void setM(int x) {_m = x;}
	void setY(int x) {_y = x;}

	void print(){
		cout << _m << " " << _d << " " << _y << endl;
	}

	Date operator+(int b){ //ok
		cout << "in operator+ (int) " << endl;
		Date t = *this;
		t._d = t._d + b;
		return t;
	}
	const Date& operator++(){ //ok
		cout << "in prefix operator ++" << endl; //++d;
		_d = _d + 1;
		return *this;
	}
	const Date operator++(int){
		cout << "in postfix operator ++" << endl; //d++;
		Date t = *this;
		_d = _d + 1;
		return t;
	}
	int operator[](int x){
		// pre: parameter must be 0, 1, or 2
		// post: corresponding month, day, year, -1 returned if error. Has significant code so make a private functions
		if (x == 0) return _m;
		if (x == 1) return _d;
		if (x == 2) return _y;
		return -1;
	}
	void operator()(string s){
		cout << "in operator ()" << endl;
		convert(s);
	}
	int operator()(int x){
		// pre: parameter must be 0, 1, or 2
		// post: corresponding month, day, year, -1 returned if error. Has significant code so make a private functions
		if (x == 0) return _m;
		if (x == 1) return _d;
		if (x == 2) return _y;
		return -1;
	}
	/*operator string(){
		cout << "in the string type conversion operator" << endl;
		return convert2();
	}
	*/
	operator char*(){
		cout << "char* type conversion operator" << endl;
		return convert3();
	}
	const Date& operator=(string b){
		cout << "in operator= " << endl;
		convert(b);
		return *this;
	}
};
ostream& operator<<(ostream& out, const Date& b){
	out << " in operator " << endl;
	out << b.getM() << " " << b.getD() << " " << b.getY() << endl;
	return out;
}
Date operator+(int x, const Date& b){
		cout << "in operator+ (int, Date) " << endl;
		Date t = b;
		t.setD(t.getD() + x);
		return t;
	}

int main(){
	Date d; // default constructor
	d.print();
	Date d2(10, 16, 2020);
	d2.print();

	return 1;
}
