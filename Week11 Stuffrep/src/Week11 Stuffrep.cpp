//============================================================================
// Name        : Week11.cpp
// Author      : luis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class MyObject{
private:
    string _stuff;
public:
    MyObject(){}
    MyObject(string s):_stuff(s){}
    void setStuff(string s){_stuff = s;}
    string getStuff(){return _stuff;}
};

class ObjectNode{
private:
    MyObject _data;
    ObjectNode* _next;
public:
    ObjectNode():_data(MyObject("")), _next(nullptr){}
    ObjectNode(string s, ObjectNode* n):_data(MyObject(s)), _next(n){}
    friend class StuffRep;
};

class StuffRep{
private:
	ObjectNode* _object;
	string** _type;
	int _size;
	int _rctr;
public:
	StuffRep(){_object = NULL; _type = NULL; _size=0;}
	StuffRep(int x){
		_object = new ObjectNode();
		ObjectNode* t = _object, * t2;
		for (int i=1; i<x; i++){
			t2 = new ObjectNode();
			t->_next = t2;
			t = t2;
		}
		_type = new string*[x];
		for (int i=0; i<x; i++){
			_type[i] = new string("");
		}
		_size = x;
	}
	void modifyObject(int slot, string s1, string s2){
		ObjectNode* t = _object;
		for (int i=0; i<slot; i++){
			t = t->_next;
		}
		t->_data.setStuff(s1);
		_type[slot] = new string(s2);
	}
	void print(){
		ObjectNode* t = _object;
		for (int i=0; i<_size; i++){
			cout << "slot " << i << " " << t->_data.getStuff() << " " << *_type[i] << endl;
			t = t->_next; // added to move down the pointer
		}
	}
};
class Stuff{
private:
	StuffRep* _rep;
public:

};
int main() {
	StuffRep s(3);
	s.print();
	s.modifyObject(1, "A", "B");
	s.print();
	return 0;
}
