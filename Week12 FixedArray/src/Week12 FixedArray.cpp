//============================================================================
// Name        : Week12.cpp
// Author      : luis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <vector>
#include <iostream>
#include <assert.h> // a way for error checking.
using namespace std;

template<class T, int SIZE>
class FixedArray{
private:
	T _elements[SIZE];
	static T _dval;
public:
	FixedArray(){
		for(int i=0; i<SIZE; i++){
			_elements[i] = _dval;
		}
	}
	T& operator[](int);
	T operator[](int) const;
};
template<class T, int SIZE>
T FixedArray<T, SIZE>::_dval;

template<class T, int SIZE>
T& FixedArray<T,SIZE>::operator[](int b){
	cout << "[] return T&" << endl;
	assert (b < SIZE);
	return _elements[b];
}

template<class T, int SIZE>
T FixedArray<T,SIZE>::operator[](int b) const{
	cout << "[] return T" << endl;
	assert (b < SIZE);
	return _elements[b];
}

template<class T, int SIZE>
ostream& operator<<(ostream& out, const FixedArray<T,SIZE>& b){
	for(int i=0; i<SIZE; i++){
		out << b[i] << " ";
	}
	return out;
}

int main() {
	FixedArray<int, 5> m;
	m[0] = 12;
	m[4] = 14;
	cout << m << endl;

	return 0;
}
