#include <iostream>
using namespace std;

class Node{
private:
    int _data;
    Node* _next;
public:
    Node(): _data(0), _next(nullptr) {}
    Node(int d, Node* n): _data(d), _next(n) {}
    friend class LinkedList;
    friend class ListRep;
};

class ListRep{
private:
    Node* _head;
    Node* _tail;
    int _rctr;
    void free(){
        Node* n = _head;
        while (n != nullptr){
            Node* t = n->_next;
            delete n;
            n = t;
        }
    }
    void copy(const ListRep& b){
    	_rctr = 1;
        if (b._head == nullptr){
            _head = _tail = nullptr;
            return;
        }
        Node* newnode = new Node(b._head->_data, nullptr);
        _head = newnode;
        Node* prev = _head;
        Node* temp = b._head->_next;
        while (temp != nullptr){
            newnode = new Node(temp->_data, nullptr);
            prev->_next = newnode;
            temp = temp->_next;
            prev = prev->_next;
        }
        _tail = prev;
    }
public:
    ListRep(){
    	_head = _tail = nullptr;
    	_rctr = 1;
    }

    ListRep(const ListRep& b){
    	cout << "in LIstRep copy constructor" << endl;
        copy(b);
    }

    ~ListRep(){
    	cout << "in ListRep destructor" << endl;
        free();
    }

    const ListRep& operator=(const ListRep& b){
    	cout << "in ListRep operator=" << endl;
    	if (this != &b){
            free();
            copy(b);
        }
        return *this;
    }

    friend class LinkedList;
};

class LinkedList{
private:
	ListRep* _rep;
    void unique(){ // ********* make a deep copy when if there is more than one thing
    	cout << "in unique"	<< endl;	// pointing to the list ****************
    	if (_rep->_rctr == 1) return;
    	_rep->_rctr--;
    	_rep = new ListRep(*_rep);
    }
public:
	LinkedList(){
		cout << "in LinkedList default constructor" << endl;
		_rep = new ListRep();
	}
	LinkedList(const LinkedList& b){
		cout << "in LinkedList copy constructor" << endl;
		_rep = b._rep;
		_rep->_rctr++;   // or b._rep->_rctr++;
	}
	~LinkedList(){
		cout << "in LinkedList destructor" << endl;
		_rep->_rctr--;
		if (_rep->_rctr == 0){
			delete _rep;
		}
	}
	const LinkedList& operator=(const LinkedList& b){
		cout << "in operator=" << endl;
		if (this != &b){
			_rep->_rctr--;
			if (_rep->_rctr == 0){
				delete _rep;
			}
			_rep = b._rep;
			_rep->_rctr++;   // or b._rep->_rctr++;
		}
		return *this;
	}
	void addHead(int a){
		unique(); // make deep copy if needed
		Node* n = new Node(a, _rep->_head);
		_rep->_head = n;
		if (_rep->_tail == nullptr){
			_rep->_tail = n;
		}
	}
	void print(ostream &outfile){
		Node* n = _rep->_head;
		while(n != nullptr){
			outfile << n->_data << " ";
			n = n->_next;
		}
		cout << "" <<  _rep->_rctr << endl;
		outfile << endl;
	}
};
int main() {
	LinkedList m, n;
	m.addHead(6);
	m.addHead(7);
	cout << "printing m: ";
	m.print(cout);

	n = m;
	cout << "printing n: ";
	n.print(cout);

	n.addHead(8);
	cout << "printing n after adding 8: ";
	n.print(cout);

	cout << "printing m: ";
	m.print(cout);
	return 0;
}
