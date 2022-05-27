
#include <iostream>
using namespace std;
class Stuff{
private:
	int x;
	int *y;
	int **z;
public:
	Stuff(int a, int b){
		cout << "in default constructor" << endl;
		x = 12;
		y = new int(a+b);
		z = &y;
	}
	~Stuff(){
		cout << "in destructor" << endl;
		delete y;
	}

	const Stuff& operator=(const Stuff& b){
		cout << "in oper= constructor" << endl;
		if (this != &b){
			delete y;
			x = b.x;
			y = new int(*(b.y));
			z = &y;
		}
		return *this;
	}
	void print(){
		cout << "printing " << &*this << endl;
		cout << "x: " << &x << " " << x << endl;
		cout << "y: " << &y << " " << y << " " << *y << endl;
		cout << "z: " << &z << " " << z << " " << *z << " " << **z << endl;
	}
};
int main() {

	Stuff s(10,5);
	s.print();



	/*
	int *a = new int(12);
	int *b = &*a;
    cout << *a << " " << *b << endl;
    */
	return 0;
}
