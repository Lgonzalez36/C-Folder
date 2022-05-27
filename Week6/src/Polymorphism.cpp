using namespace std;
#include <iostream>
#include <vector>
class Employee{
public:
	Employee(){
		cout << "\tin employee default constructor" << endl;
	}
	Employee(string n, int id)
		:_name(n), _id(id){
		cout << "\tin employee n-arg constructor" << endl;
	}
	virtual ~Employee(){cout << "\t\tin Employee destructor" << endl;}
	void setName(string n){_name = n;}
	string getName(){return _name;}
	void setID(int n){_id = n;}
	int getID(){return _id;}
	virtual void print(){
		cout << "\tin employee print" << endl;
		cout << "\t" << _name << " " << _id << endl;
	}
private:
	string _name;
	int _id;
};

class Manager : public Employee{
public:
	Manager(string n, int id, int b)
		: Employee(n, id){
		cout << "\tin manager n-arg constructor" << endl;
		_bonus = b;
	}
	virtual ~Manager(){cout << "\t\tin Manager destructor" << endl;}
	void setBonus(int n){_bonus = n;}
	int getBonus(){return _bonus;}

	virtual void print(){
		cout << "\tin manager print" << endl;
		Employee::print();
		cout << "\t" << _bonus << endl;
	}

	// employee public methods are accessible inside any manager methods and
	// in main by manager objects

private:
	int _bonus;
};

class WarehouseManager : public Manager{
public:
	WarehouseManager(string n, int id, int b, char wl)
		: Manager(n, id, b){
		cout << "\tin warehouse manager n-arg constructor" << endl;
		_whloc = wl;
	}
	virtual ~WarehouseManager(){cout << "\t\tin Warehouse Manager destructor" << endl;}
	void setWLoc(char n){_whloc = n;}
	char getWLoc(){return _whloc;}

	virtual void print(){
		cout << "\tin warehouse manager print" << endl;
		Manager::print();
		cout << "\t" << _whloc << endl;
	}
private:
	char _whloc;
};

class Employees{  // shows association with
public:
	Employees(){}
	~Employees(){
		cout << "\tin employees destructor" << endl;
		for (int i=0; i<emps.size(); i++){
			delete emps[i];
		}
	}
	void addEmployee(string n, int id, int b=0, char wl='\0'){  // using default params
		if (b==0)
			emps.push_back(new Employee(n, id));
		else if (wl == '\0')
			emps.push_back(new Manager(n, id, b));
		else
			emps.push_back(new WarehouseManager(n, id, b, wl));
	}
	void addBonus(int x){
		for(int i=0; i<emps.size(); i++){
			Manager* mptr = dynamic_cast<Manager*>(emps[i]);
			if (mptr != nullptr)
				mptr->setBonus(mptr->getBonus() + x);
			else{
				WarehouseManager* wptr = dynamic_cast<WarehouseManager*>(emps[i]);
				if (wptr != nullptr)
					wptr->setBonus(wptr->getBonus() + x);
			}
		}
	}
	void print(){
		for (int i=0; i<emps.size(); i++){
			emps[i]->print();
		}
	}
private:
	vector<Employee*> emps;
};

int main(){
	Employees emps;
	cout << "instantiating Employee" << endl;
	emps.addEmployee("mary", 100);
	cout << "instantiating Manager" << endl;
	emps.addEmployee("tom", 101, 1000);
	cout << "instantiating Warehouse Manager" << endl;
	emps.addEmployee("sara", 102, 2000, 'A');
	cout << "printing employees" << endl;
	emps.print();
	emps.addBonus(100);
	emps.print();
	return 0;
}
