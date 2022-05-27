//============================================================================
// Name        : Week13.cpp
// Author      : luis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

// using a forward reference
template<class T> class SmartPtr;

template<class T>
class SmartPtrRep{
	private:
		SmartPtrRep(const T& t)
			:_obj(t),
			 _rctr(1){
			cout << "\tin SmartPtrRep one arg constructor" << endl;
		}
		~SmartPtrRep(){
			cout << "\tin SmartPtrRep Destructor" << endl;
		}
		T _obj;
		int _rctr;
	friend class SmartPtr<T>;
};

template<class T>
class SmartPtr{
	private:
		SmartPtrRep<T>* _ptr; // data type of ptr is point to a SmartPtrRep object of type T
		void copy(const SmartPtr<T>& b){ //used in destructor
			if (b._ptr != nullptr)
				b._ptr->_rctr++;
			_ptr = b._ptr;
		}
		void free(){ // used in destructor
			if (_ptr != nullptr){
				_ptr->_rctr--;
				if (_ptr->_rctr == 0)
					delete _ptr;
			}
		}
	public:
		SmartPtr():_ptr(0){
			cout << "\tin default smartptr" << endl;
		}
		SmartPtr(const T& t)
			: _ptr(new SmartPtrRep<T>(t)){
			cout << "\tin one arg smartptr const" << endl;
		}
		SmartPtr(const SmartPtr<T>& b){
			cout << "\tin copy smartptr const" << endl;
			copy(b);
		}
		~SmartPtr(){
			cout << "\tin smartptr destructor" << endl;
			cout << "\trctr " << _ptr->_rctr << " destroying ptr " << endl;
			free();
		}
		T& operator*(){
			cout << "\tin oper*" << endl;
			assert(_ptr!=nullptr);
			return _ptr->_obj;
		}
		const T& operator*() const{
			cout << "\tin oper* const" << endl;
			assert(_ptr!=nullptr);
			return _ptr->_obj;
		}
		T* operator->(){
			cout << "\tin oper->" << endl;
			assert(_ptr!=nullptr);
			return &_ptr->_obj;
		}
		const T* operator->() const{
			cout << "\tin oper-> const" << endl;
			assert(_ptr!=nullptr);
			return &_ptr->_obj;
		}
		SmartPtr<T> operator=(SmartPtr<T> b){
			cout << "\tin oper= param SmartPtr" << endl;
			if (this != &b){
				free();
				copy(b);
			}
		}
		SmartPtr<T> operator=(const T& t){
			cout << "\tin oper= param T" << endl;
			free();
			_ptr = new SmartPtrRep<T>(t);
			return *this;
		}
};
template <class T>
void Test(SmartPtr<T> tptr){
	int x = 12;
	cout << "in Test - before oper=" << endl;
	tptr = x;
	cout << "in Test - before oper*" << endl;
	cout << *tptr << endl;
	cout << "in Test - before return" << endl;
}

int main() {
	cout << "statement 1" << endl;
	SmartPtr<int> iptr(4);
	cout << "\nstatement 2" << endl;
	cout << *iptr << endl;
	cout << "\nstatement 3" << endl;
	*iptr = 7;
	cout << "\nstatement 4" << endl;
	cout << *iptr << endl;
	cout << "\nstatement 5" << endl;
	SmartPtr<int> iptr2 = iptr;  // iptr2(iptr)

	cout << *iptr << endl;
	Test(iptr);
	cout << *iptr << endl;

	cout << "before return" << endl;
	return 0;
}
