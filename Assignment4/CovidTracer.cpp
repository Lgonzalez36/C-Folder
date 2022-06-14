
//============================================================================
// Name        : Assignment4.cpp
// Author      : Luis Gonzalez
// Version     :
// Copyright   : Your copyright notice
// Description : Covid Tracker in C++, Ansi-style
//============================================================================
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <bits/stdc++.h>
#include <algorithm>
#include <iomanip>

using namespace std;
class Person{
private:
	int _pid;
	string _fname;
	string _lname;
	string _email;
public:
	Person(){}
	Person(int p, string fn, string ln, string em){
		_pid = p;
		_fname = fn;
		_lname = ln;
		_email = em;
	}
	/*
	 * Basic getters and setters
	 */
	virtual ~Person(){cout << "\t\tin Person destructor" << endl;}
	void setPid(int p){_pid = p;}
	void setFname(string fn){_fname = fn;}
	void setLname(string ln){_lname = ln;}
	void setEmail(string em){_email = em;}
	int getPid()const {return _pid;}
	string getFname()const {return _fname;}
	string getLname()const {return _lname;}
	string getEmail()const {return _email;}
};

class Case{
private:
	Date _diagDate;
	int _cid;
	int _pid;
	int _whoConf;
	int _caseStatus;
	int _numOriginal;
	int _numAssociated;
	int _contacted;
	int _diagnosis;
	vector<int> _original;
	vector<int> _associated;
public:
	Case(){}
	Case(int cid, int pid, int contacted,int diagnos, int whoConf,  int caseStat){
		_cid = cid;
		_pid = pid;
		_contacted = contacted;
		_whoConf = whoConf;
		_diagnosis = diagnos;
		_caseStatus = caseStat;
		_numOriginal = 0;
		_numAssociated = 0;
	}
	virtual ~Case(){cout << "\t\tin Case destructor" << endl;}
	/*
	 * Basic getters and setters for class object
	 */
	void setCid(int cid){_cid = cid;}
	void setPid(int p){_pid = p;}
	void setContacted(int cont){ _contacted = cont;}
	void setWhoConf(int w){_whoConf = w;}
	void setDiagnosis(int d){_diagnosis = d;}
	void setCaseStatus(int cs){_caseStatus= cs;}
	void setCaseDate(string date){_diagDate = date;}
	void setNumAssociated(int numAsso){_numAssociated = numAsso;}
	void setNumOriginal(int numOrig){_numOriginal = numOrig;}
	void getCaseDate(){cout << '\t' << _diagDate.getM() << '/' << _diagDate.getD() << '/' << _diagDate.getY() << endl;}
	int getCid()const {return _cid;}
	int getPid()const {return _pid;}
	int getContacted()const {return _contacted;}
	int getWhoConf()const {return _whoConf;}
	int getDiagnosis()const {return _diagnosis;}
	int getcaseStatus()const {return _caseStatus;}
	int getNumAssociated()const {return _numAssociated;}
	int getNumOriginal()const {return _numOriginal;}

	// associated
	/*
	 * Pre: none
	 * Post: @returns Total number of associated cases
	 * 		 @returns -10 slot if slot is not in range
	 */
	int getAssociated(int slot){
		if (slot >= 0 && slot < _numAssociated){ return _associated[slot];}
		else return -10;
	}
	/*
	 * Pre: none
	 * Post: @returns Parent case from vector
	 * 		 @returns -10 slot if slot is not in range
	 */
	int getOriginal(int slot){
		if (slot >= 0 && slot < _numOriginal){ return _original[slot];}
		else return -10;
	}
	/*
	 * Pre: Associated vector is unchanged
	 * Post: Adds an associated case to the end of the vector
	 */
	void addAssociated(int asso){_associated.push_back(asso);}
	/*
	 * Pre: Associated vector is unchanged
	 * Post: Supposed to remove an associated case from the vector
	 */
	void removeAssociated(int slot){_associated.erase(std::remove(_associated.begin(), _associated.end(), slot));}

	// original *** not sure if original need other methods
	/*
	 * Pre: Original vector is unchanged
	 * Post: adds parent case to the vector
	 */
	void addOriginal(int ori){_original.push_back(ori);}
};

class Symptoms{
private:
	int _numSymptoms;
	vector<string> _symptoms;	// {fatigue, cough, sore throat}
	vector<int> _confirmed;		// {1, 0, 0}
	vector<int> _severity;		// {2, 2, 4}
public:
	Symptoms();
	Symptoms(int numSympt){_numSymptoms = numSympt;}
	virtual ~Symptoms(){cout << "\t\tin Symptoms destructor" << endl;}
	/*
	 * Pre: none
	 * Post: Basic setters and getters
	 */
	void setNumSymotoms(){_numSymptoms++;} // increase number every time new symptom is added
	int getNumSymptoms()const {return _numSymptoms;}

	// _symptoms
	/*
	 * Pre: none
	 * Post: @returns symptom from vector
	 * 		 @returns empty string if none where found
	 */
	string getSymptom(int loc){
		if (loc >= 0 && loc < _numSymptoms) {return _symptoms[loc];}
		else return "";
	}
	/*
	 * Pre: _symptom vector is unchanged
	 * Post: adds symptom to the vector
	 */
	void addSymptom(string s){_symptoms.push_back(s);}
	/*
	 * Pre: _symptom vector is unchanged
	 * Post: removes Symptom from a given location
	 */
	void removeSymptom(int slot) {_symptoms.erase(_symptoms.begin()+ slot);}

	// _confirmed
	/*
	 * Pre: none
	 * Post: @returns an element in the vector. This vector hold 0 or 1 and
	 * 		 returns to check if a symptom was confirmed or not
	 */
	int getConfirmed(int slot){
		int confirmedSize = _confirmed.size();
		if (slot >= 0 && slot < confirmedSize) {return _confirmed[slot];}
		return -100;
	}
	/*
	 * Pre: none
	 * Post: adds to the confirmed symptoms vector
	 */
	void addConfirmed(int slot){_confirmed.push_back(slot);}
	/*
	 * Pre: none
	 * Post: deletes element in the vector
	 */
	void removeConfirmed(int slot) {_confirmed.erase(std::remove(_confirmed.begin(), _confirmed.end(), slot));}
	/*
	 * Pre: none
	 * Post: modifies confirmed vector to update if symptom is confirmed to not
	 */
	void modifyConfirmed(int slot){
		if(_confirmed.at(slot-1) == 0) {_confirmed.at(slot-1) = 1;}
		else if (_confirmed.at(slot-1) == 1) {_confirmed.at(slot-1) = 0;}
	}

	// _severity
	/*
	 * Pre: none
	 * Post: @returns the severity of a symptom ex 1-5
	 * 	 	 returns error if slot is not in range
	 */
	int getSeverity(int slot){
		int severitySize = _severity.size();
		if (slot >= 0 && slot < severitySize) {return _severity[slot];}
		else return -200;
	}
	/*
	 * Pre: none
	 * Post: method adds severity to the end of the vector
	 */
	void addSeverity(int sevr){_severity.push_back(sevr);}
	/*
	 * Pre: none
	 * Post: @returns symptom from vector
	 * 		 @returns empty string if none where found
	 */
	void removeSeverity(int slot){
		cout << " before erasing: " << _severity.size() << endl;
		_confirmed.erase(std::remove(_severity.begin(), _severity.end(), slot));
		cout << " after erasing: " << _severity.size() << endl;
	}
	/*
	 * Pre: none
	 * Post: method modifies the severity of an element in the vector
	 */
	void modifySeverity(int slot, int updated){_severity.at(slot-1) = updated;}
};

class AllPersons{
private:
	vector<Person*> _persons;
public:
	AllPersons(){} 	//Class Ctor
	~AllPersons(){ 	//Class destructor
		int personsSize = _persons.size();
		for(int i=0; i < personsSize; i++){
			delete _persons[i];
		}
	}
	/*
	 * Pre: none
	 * Post: instantiates new Person object and adds it to the vector
	 */
	void addPerson(int pid, string fn, string ln, string em){
		_persons.push_back(new Person(pid,fn,ln,em));
	}
	/*
	 * Pre: none
	 * Post: instantiates new Person object and adds it to the vector
	 */
	void addPerson(string pid, string fn, string ln, string em){
		int pidint = stoi(pid);
		_persons.push_back(new Person(pidint,fn,ln,em));
	}
	/*
	 * Pre: none
	 * Post: basic setters and getters
	 */
	void removePerson(int pid){delete _persons[pid];}
	void modifyPersonEmail(int pid, string em){_persons.at(pid-1)->setEmail(em);}
	void modifyPersonFname(int pid, string fn){_persons.at(pid-1)->setFname(fn);}
	void modifyPersonLname(int pid, string ln){_persons.at(pid-1)->setLname(ln);}
	int getPersonID (int pid)const {return _persons.at(pid-1)->getPid();}
	string getPersonFname (int pid)const {return _persons.at(pid-1)->getFname();}
	string getPersonLname (int pid)const {return _persons.at(pid-1)->getLname();}
	string getPersonEmail (int pid)const {return _persons.at(pid-1)->getEmail();}
};

class AllCases{
private:
	vector<Case*> _cases;
public:
	AllCases(){}	// Class Ctor
	~AllCases(){	// Class destructor
		int caseSize = _cases.size();
		for(int i=0; i < caseSize; i++){
			delete _cases[i];
		}
	}
	/*
	 * Pre: none
	 * Post: instantiates new Case object and adds it to the vector
	 */
	void addCase(int newCid, int newPid){
		_cases.push_back(new Case(newCid, newPid, 0, 0, -1, 0));
	}
	/*
	 * Pre: none
	 * Post: instantiates new Person object and adds it to the vector
	 */
	void addCase(string cid, string pid, string contacted, string diagnos, string whoConf, string caseStat){
		int cidInt = stoi(cid);
		int pidint = stoi(pid);
		int contactint = stoi(contacted);
		int whoconfint = stoi(whoConf);
		int diagnosint = stoi(diagnos);
		int caseStatint = stoi(caseStat);
		_cases.push_back(new Case(cidInt, pidint, contactint, diagnosint, whoconfint, caseStatint));
	}
	/*
	 * Pre: Case object has been created
	 * Post: sets new information to the case
	 */
	void addToCaseDiagnosis(int cid, string date, string diagnosis, string whoDiagnosed){
		int diagnoInt = stoi(diagnosis);
		int whoDiagnosInt = stoi(whoDiagnosed);
		_cases.at(cid-1)->setDiagnosis(diagnoInt);
		_cases.at(cid-1)->setWhoConf(whoDiagnosInt);
		_cases.at(cid-1)->setCaseDate(date);
	}
	/*
	 * Pre: Case object has been created
	 * Post: sets new information to the case
	 */
	void addToCaseOrignal(int cid, string original){
		int origInt = stoi(original);
		_cases.at(cid-1)->addOriginal(origInt);
	}
	/*
	 * Pre: Case object has been created
	 * Post: sets new information to the case
	 */
	void addToCaseOrignal(int newCid, int originalCid) {_cases.at(newCid-1)->addOriginal(originalCid);}
	/*
	 * Pre: Case object has been created
	 * Post: sets new information to the case
	 */
	void addToCaseAssociated(int cid, string asso){
		int assoInt = stoi(asso);
		_cases.at(cid-1)->addAssociated(assoInt);
	}
	/*
	 * Pre: Case object has been created
	 * Post: sets new information to the case
	 */
	void addToCaseDate(int cid, string date){
		date.erase(std::remove(date.begin(), date.end(), ' '));
		_cases.at(cid-1)->setCaseDate(date);
	}
	void modifyCaseNumAssociated(int cid, int asso) {_cases.at(cid-1)->setNumAssociated(asso);}
	void modifyCaseCotacted(int cid, int updated) {_cases.at(cid-1)->setContacted(updated);}
	void modifyCaseStatus(int cid, int updated) {_cases.at(cid-1)->setCaseStatus(updated);}
	void modifyCaseDiagnosis(int cid, int updated) {_cases.at(cid-1)->setDiagnosis(updated);}
	void modifyCaseDate(int cid, string date) {_cases.at(cid-1)->setCaseDate(date);}
	void modifyCaseWhoConf(int cid, int updated) {_cases.at(cid-1)->setWhoConf(updated);}
	void removeCaseAssociated(int cid, int asso) {_cases.at(cid-1)->removeAssociated(asso);}
	void getCaseDate(int cid) { _cases.at(cid-1)->getCaseDate();}
	int getCaseCid(int cid)const {return _cases.at(cid-1)->getCid();}
	int getCasePid(int cid)const {return _cases.at(cid-1)->getPid();}
	int getCaseDiagnosis(int cid)const {return _cases.at(cid-1)->getDiagnosis();}
	int getCaseWhoConf(int cid)const {return _cases.at(cid-1)->getWhoConf();}
	int getCaseStatus(int cid)const {return _cases.at(cid-1)->getcaseStatus();}
	int getCaseNumOriginal(int cid)const {return _cases.at(cid-1)->getNumOriginal();}
	int getCaseNumAssociated(int cid) const {return _cases.at(cid-1)->getNumAssociated();}
	int getCaseContacted(int cid)const {return _cases.at(cid-1)->getContacted();}
	int getCaseOriginalList(int cid) {return _cases.at(cid-1)->getOriginal(cid);}
	int getCaseAssociatedList(int cid, int i) {return _cases.at(cid-1)->getAssociated(i);}
	int getCaseTotalNumber()const {return _cases.size();}
};

class AllSymptoms{
private:
	vector<Symptoms*> _symptoms;
	vector<string> symptomsList; // Populates from given file
public:
	AllSymptoms(){} 	//Class Ctor
	~AllSymptoms(){ 	//Class destructor
		int symptomsSize = _symptoms.size();
		for(int i=0; i < symptomsSize; i++){
			delete _symptoms[i];
		}
	}
	/*
	 * Pre: instantiates new Symptom object
	 * Post: add newly created object to vector
	 */
	void addSymptoms( int numsympt) {_symptoms.push_back(new Symptoms(numsympt));}
	/*
	 * Pre: Case object has been created
	 * Post: sets new information to the case
	 */
	void addSymptoms(int cid, string symp, string conf, string sever){
		int confint, severint;
		confint = stoi(conf);
		severint = stoi(sever);
		_symptoms.at(cid-1)->addSymptom(symp);
		_symptoms.at(cid-1)->addConfirmed(confint);
		_symptoms.at(cid-1)->addSeverity(severint);
	}
	/*
	 * Pre: Case object has been created
	 * Post: sets new information to the case
	 */
	void addToSymptoms(int cid, string sympt) {_symptoms.at(cid-1)->addSymptom(sympt);}
	/*
	 * Pre: Case object has been created
	 * Post: sets new information to the case
	 *  	 converts string @param to int
	 */
	void addToSeverity(int cid, string severity){
		int severityInt = stoi(severity);
		_symptoms.at(cid-1)->addSeverity(severityInt);
	}
	/*
	 * Pre: Case object has been created
	 * Post: sets new information to the case
	 *  	 converts string @param to int
	 */
	void addToConfirmed(int cid, string confirmed){
		int confint = stoi(confirmed);
		_symptoms.at(cid-1)->addConfirmed(confint);
	}
	void addSymptomList(string symptom) {symptomsList.push_back(symptom);}
	void modifySymptomSeverity(int cid, int loc, int updated) {_symptoms.at(cid-1)->modifySeverity(loc, updated);}
	void modifyConfirmation(int cid, int loc) {_symptoms.at(cid-1)->modifyConfirmed(loc);}
	void modifyNumSymptom(int cid) {_symptoms.at(cid-1)->setNumSymotoms();}
	int getSeverity(int cid, int i) {return _symptoms.at(cid-1)->getSeverity(i);}
	int getConfirmed(int cid, int i) {return _symptoms.at(cid-1)->getConfirmed(i);}
	int getListSize() {return symptomsList.size();}
	int getNumSymptoms(int loc) {return _symptoms.at(loc-1)->getNumSymptoms();}
	string getSymptom(int cid, int i) {return _symptoms.at(cid-1)->getSymptom(i);}
	string getSymptomFromList(int loc) {return symptomsList.at(loc-1);}
	/*
	 * Pre: none
	 * Post: prints all the known symptoms from the given file
	 */
	void printListSize(){
		int symptomsListSize = symptomsList.size();
		for(int i=0; i < symptomsListSize; i++){
			cout << i+1 << ")  " << symptomsList.at(i) << endl;
		}
	}
};
/*
 * Pre: unopen file none objects created
 * Post: takes given file and sorts information to the right objects
 *
 * 	file is read line by line, then substring comma by comma
 * 	to sort the information correctly. file is then closed at the end of method
 */
void scanCaseFile(AllSymptoms &_symptoms, AllCases &_cases, AllPersons &_persons, string filename){
	string line,tempString;
	ifstream readCases(filename);
	if(!readCases.is_open()){
		cout << "ERROR: Case File failed to open" << endl;
		readCases.close();
	}
	int numSympt, cid;
	vector<string> splicedLine;
	while(getline(readCases,line)){
		cout << line << endl;
		stringstream ss(line);
		while(getline(ss, tempString, ',')){
			splicedLine.push_back(tempString);
		}
		numSympt = stoi(splicedLine.at(6)); //num of symptoms
		cid = stoi(splicedLine.at(0));
		_persons.addPerson(splicedLine.at(1), splicedLine.at(2), splicedLine.at(3), splicedLine.at(4));
		int dateLocation = (7 + (numSympt * 3));
		int firstSection = (dateLocation - (numSympt * 3));
		int secondSection = (dateLocation - (numSympt * 2));
		int thirdSection = (dateLocation - numSympt);
		_symptoms.addSymptoms(numSympt);
		if(numSympt > 0){
			for(int i=7; i<dateLocation; i++){
				if (i>(firstSection-1) && i<secondSection){
					_symptoms.addToSymptoms(cid, splicedLine.at(i));
				}
				if (i>(secondSection-1) && i<thirdSection){
					_symptoms.addToConfirmed(cid, splicedLine.at(i));
				}
				if (i>(thirdSection -1)){
					_symptoms.addToSeverity(cid, splicedLine.at(i));
				}
			}
		}
		int origLocation = dateLocation + 3;
		int assoLocation = dateLocation + 4;
		int origValue = stoi(splicedLine.at(origLocation));
		int assoValue = stoi(splicedLine.at(assoLocation));
		if (origValue == 0 && assoValue == 0){
			_cases.addCase(splicedLine.at(0), splicedLine.at(1), splicedLine.at(5), splicedLine.at(dateLocation + 1), splicedLine.at(dateLocation + 2), splicedLine.back());
			_cases.addToCaseDate(cid, splicedLine.at(dateLocation));
			splicedLine.clear();
		}
		if(origValue == 0 && assoValue > 0 ){
			assoLocation = origLocation + 1;
			assoValue = stoi(splicedLine.at(assoLocation));
			_cases.addCase(splicedLine.at(0), splicedLine.at(1), splicedLine.at(5), splicedLine.at(dateLocation + 1), splicedLine.at(dateLocation + 2), splicedLine.back());
			_cases.modifyCaseNumAssociated(cid, assoValue);
			_cases.addToCaseDate(cid, splicedLine.at(dateLocation));
			for(int i=0; i < assoValue; i++){
				_cases.addToCaseAssociated(cid,splicedLine.at(assoLocation+i+1));
			}
			splicedLine.clear();
		}
		if(origValue > 0){
			_cases.addCase(splicedLine.at(0), splicedLine.at(1), splicedLine.at(5), splicedLine.at(dateLocation + 1), splicedLine.at(dateLocation + 2), splicedLine.back());
			_cases.addToCaseDate(cid, splicedLine.at(dateLocation));
			for(int i=0; i < origValue; i++){
				_cases.addToCaseOrignal(cid, splicedLine.at(origLocation+i+1));
			}
			assoLocation = (origLocation + origValue + 1);
			assoValue = stoi(splicedLine.at(assoLocation));
			_cases.modifyCaseNumAssociated(cid, assoValue);
			for(int i=0; i < assoValue; i++){
				_cases.addToCaseAssociated(cid,splicedLine.at(assoLocation+i+1));
			}
			splicedLine.clear();
		}
	}
	readCases.close();
}
/*
 * Pre: unopen file
 * Post: takes given file and reads information line by line
 *  	 then adds each symptom to a vector.
 */
void scanSymptomFile(AllSymptoms &_symptoms, string filename){
	string line;
	ifstream readSymptoms(filename);
	if(!readSymptoms.is_open()){
		cout << "ERROR: Symptom File failed to open" << endl;
		readSymptoms.close();
	}
	while(getline(readSymptoms,line)) {_symptoms.addSymptomList(line);}
	cout << "Size of List" << _symptoms.getListSize() << endl;
	readSymptoms.close();
}
/*
 * Pre: user is navigating thru other menus
 * Post: prints out instructions to enter a case Id
 */
int printViewCaseSubMenu(){
	int userInput;
	cout << "Enter CaseId to Open a Case:                    " << endl;
	cout << "________________________________________________" << '\n' << endl;
	cin >> userInput;
	return userInput;
}
/*
 * Pre: user is navigating thru other menus
 * Post: prints out main menu and
 *  	 @returns a user input as an int
 */
int printMainMenu(){
	int userInput;
	cout << "________________________________________________" << '\n' << endl;
	cout << "            Welcome to the Main Menu            " << endl;
	cout << "________________________________________________" << endl; //////////
	cout << "View Case by CaseId..........................(1)" << endl; /// done!!
	cout << "View All Open Cases..........................(2)" << endl; /// done!!
	cout << "View List of uncontacted from a case.........(3)" << endl; /// done!!
	cout << "Edit a Case by entering CaseID...............(4)" << endl; /// done... sort of!!
	cout << "Exit Program.................................(5)" << endl; //////////
	cout << "________________________________________________" << '\n' << endl;
	cin >> userInput;
	return userInput;
}
/*
 * Pre: user is navigating thru other menus
 * Post: prints out modify main menu and
 *  	 @returns a user input as an int
 */
int printEditCaseMainMenu(){
	int userInput;
	cout << "________________________________________________" << '\n' << endl;
	cout << " 	     Modify Main Menu                         " << endl;
	cout << "_________________________________________________" << endl; /////////////
	cout << "Edit Case Information.........................(1)" << endl; ///done!!
	cout << "Edit Person Information.......................(2)" << endl; ///done!!
	cout << "Edit Symptom information......................(3)" << endl; ///done!!
	cout << "_________________________________________________" << '\n' << endl; /////
	cin >> userInput;
	return userInput;
}
/*
 * Pre: user is navigating thru other menus
 * Post: prints out the modify menu and
 *  	 @returns a user input as an int
 */
int printEditCaseMenu(){
	int userInput;
	cout << "________________________________________________" << '\n' << endl;
	cout << " 	      Modify Case Menu                       " << endl;
	cout << "________________________________________________" << endl; ///////////////
	cout << "Close Case ..................................(1)" << endl; ///done??
	cout << "Edit COVID Diagnosis.........................(2)" << endl; ///done just needs defensing coding
	cout << "Update Contact Confirmation..................(3)" << endl; ///done just needs defensing coding
	cout << "Add New Contact Trace........................(4)" << endl; ///done?
	cout << "________________________________________________" << '\n' << endl; ///////
	cin >> userInput;
	return userInput;
}
/*
 * Pre: user is navigating thru other menus
 * Post: prints out the person menu and
 *  	 @returns a user input as an int
 */
int printEditPersonMenu(){
	int userInput;
	cout << "________________________________________________" << '\n' << endl;
	cout << " 	      Modify Person Menu                     " << endl; ///////////////
	cout << "________________________________________________" << endl; ///done
	cout << "Edit First Name..............................(1)" << endl; ///done
	cout << "Edit Last Name...............................(2)" << endl; ///done
	cout << "Edit Email...................................(3)" << endl; ///done
	cout << "________________________________________________" << '\n' << endl; ///////
	cin >> userInput;
	return userInput;
}
/*
 * Pre: user is navigating thru other menus
 * Post: prints out the modify symptom sub menu and
 *  	 @returns a user input as an int
 */
int printEditSymptomMenu(){
	int userInput;
	cout << "________________________________________________" << '\n' << endl;
	cout << " 	           Modify Symptom Menu               " << endl;
	cout << "________________________________________________" << endl; ///////////////////
	cout << "Add Symptoms.................................(1)" << endl; /// done just needs defensing coding
	cout << "Edit Severity of a Symptom...................(2)" << endl; /// done just needs defensing coding
	cout << "Edit Symptom Diagnosis.......................(3)" << endl; /// done just needs defensing coding
	cout << "Remove Symptom... ...........................(4)" << endl; /// try again later
	cout << "________________________________________________" << '\n' << endl; ////////////
	cin >> userInput;
	return userInput;
}
/*
 * Pre: user is navigating thru menu
 * Post: method closes case if and only if its children cases are closed as well
 */
void closeCase(int cid, AllCases &_cases){
	cout << "Current Case:" << '\t' << cid << endl;
	int associateID;
	int counter = 0;
	if(_cases.getCaseStatus(cid) == 1){
		cout << "TOTAL CASES:      " << _cases.getCaseTotalNumber() << endl;
		cout << "TOTAL ASSOCIATED: " << _cases.getCaseNumAssociated(cid) << endl;
		for(int i=0; i < _cases.getCaseNumAssociated(cid); i++){
			associateID =_cases.getCaseAssociatedList(cid, i);
			if(_cases.getCaseStatus(associateID) == 0){
				counter++;
				if(counter == _cases.getCaseNumAssociated(cid)){
					_cases.modifyCaseStatus(cid, 0); // to close a case
				}
			}
		}
	}
	else{
		cout << "ERROR:" << '\t' << "Case Cannot close." << endl;
		cout << "This case and/or it's associated cases are still active to close this case." << endl;
	}
}
/*
 * Pre: user is navigating thru other menus
 * Post: user enters a new case to be traced from a selected case
 *       or is able to create a new case and add primitive information of the new case
 *       this case then adds new case to its associated cases vector
 */
void AddNewTrace(int cid, AllPersons &_persons, AllCases &_cases, AllSymptoms &_symptoms){
	int newCid, newPid, input;
	bool validInput = true;
	string fn, ln, email;
	newCid = _cases.getCaseTotalNumber()+1;
	while(validInput){
		cout << "Is person new to the system?:" << endl;
		cout << "Enter 1 for yes, Enter 0 for no:" << endl;
		cin >> input;
		if(input == 0){
			newPid = newCid;
			_cases.addCase(newCid, newPid);
			_symptoms.addSymptoms(0);
			cout << "Enter First Name:" << endl;
			cin >> fn;
			cout << "Enter Last Name:" << endl;
			cin >> ln;
			cout << "Enter Email:" << endl;
			cin >> email;
			_persons.addPerson(newCid, fn, ln, email);
			_cases.addToCaseOrignal(newCid, cid);
			validInput = false;
		}
		if(input == 1){
			cout << "Enter Person ID from records:" << endl;
			cin >> newPid;
			for(int i=1; i < _cases.getCaseTotalNumber()+1; i++){
				if(newPid == _cases.getCasePid(i)){
					cout << "FOUND A MATCH: " << i << endl;
					_cases.addCase(newCid, newPid);
					_persons.addPerson(newPid, _persons.getPersonFname(newPid), _persons.getPersonLname(newPid), _persons.getPersonEmail(newPid));
					_symptoms.addSymptoms(0);
					break;
				}
			}
			validInput = false;
		}
		if(input < 0 || input > 1){
			cout << "ERROR:" << '\t' << "Invalid input try again" << endl;
		}
	}
}
/*
 * Pre: user is navigating thru other menus
 * Post: navigates user to other sub menus
 */
void enterCaseMenu(int cid, AllCases &_cases, AllPersons &_persons, AllSymptoms &_symptoms){
	int menuInput, userinput;
	string updated;
	string diagnosis;
	menuInput = ::printEditCaseMenu();
	if(menuInput == 1){
		cout << "Edit Case Status : "<< endl;
		closeCase(cid, _cases);
	}
	if(menuInput == 2){
		if(_cases.getCaseDiagnosis(cid)==1) diagnosis = "Confirmed";
		if(_cases.getCaseDiagnosis(cid)==0) diagnosis = "N/A";
		cout << "Current COVID Diagnosis:" << '\t' << diagnosis << endl;
		cout << "Enter to update Case Diagnosis:" << '\n' << "1 for confirmed covid, 0 for unconfirmed diagnosis: "<< '\n' << endl;
		cin >> userinput;
		_cases.modifyCaseDiagnosis(cid, userinput);
		cout << "Enter Confirmation Date : "<< endl;
		cout << "Enter using Format :  mm/dd/yyyy"<< endl;
		cin >> updated;
		_cases.modifyCaseDate(cid, updated);
		cout << "Enter your Employee ID to Confirm : "<< endl;
		cin >> userinput;
		_cases.modifyCaseWhoConf(cid, userinput);
	}
	if(menuInput == 3){
		cout << "Edit Contacted Confirmation : "<< endl;
		cout << "If Case has been contacted enter 1 : "<< endl;
		cout << "If Case has NOT been contacted enter 0 : "<< endl;
		cin >> userinput;
		_cases.modifyCaseCotacted(cid, userinput);
	}
	if(menuInput == 4){
		cout << "Add new Contact Trace : "<< endl;
		::AddNewTrace(cid, _persons, _cases, _symptoms);
	}
}
/*
 * Pre: user is navigating thru other menus
 * Post: navigates user to other sub menus
 */
void enterPersonMenu(int cid, AllPersons &_persons){
	int menuInput;
	string updated;
	menuInput = ::printEditPersonMenu();
	if(menuInput == 1){
		cout << "Enter First Name: "<< endl;
		cin >> updated;
		_persons.modifyPersonFname(cid, updated);
		cout << "UPDATED First Name: " <<_persons.getPersonFname(cid) << endl;
	}
	if(menuInput == 2){
		cout << "Enter Last Name: "<< endl;
		cin >> updated;
		_persons.modifyPersonLname(cid, updated);
		cout << "UPDATED Last Name: " <<_persons.getPersonLname(cid) << endl;
	}
	if(menuInput == 3){
		cout << "Enter Email: "<< endl;
		cin >> updated;
		_persons.modifyPersonEmail(cid, updated);
		cout << "UPDATED Email: " <<_persons.getPersonEmail(cid) << endl;
	}
}
/*
 * Pre: user is navigating thru other menus
 * Post: navigates user to other sub menus
 */
void enterSymptomMenu(int cid, AllSymptoms &_symptoms){
	int menuInput, userinput, size, severity;
	string updated;
	menuInput = ::printEditSymptomMenu();
	if(menuInput == 1){
		//cid = cid+1;
		cout << "Add a new Symptom : "<< endl;
		cout << "Enter Known COVID symptoms from list: " << endl;
		_symptoms.printListSize();
		cin >> userinput;
		updated = _symptoms.getSymptomFromList(userinput);
		_symptoms.addToSymptoms(cid, updated);
		cout <<"Enter Severity from 1-5: " << endl;
		cin >> updated;
		_symptoms.addToSeverity(cid, updated);
		cout << "Enter 1 if symptom is confirmed: " << endl;
		cout << "Enter 0 if symptom is NOT confirmed: " << endl;
		cin >> updated;
		_symptoms.addToConfirmed(cid, updated);
		_symptoms.modifyNumSymptom(cid);
	}
	if(menuInput == 2){
		size = _symptoms.getNumSymptoms(cid);
		cout << "Select Symptom to update Severity: " << '\n' << endl;
		cout << '\t' <<"Symptom:" << '\t' << "Severity:" << '\t' <<"Confirmed:" << endl;
		for(int i=0; i < size; i++){
			cout << i+1 << ")" << '\t' << _symptoms.getSymptom(cid, i) << '\t' << _symptoms.getSeverity(cid, i) << '\t' << _symptoms.getConfirmed(cid, i) << endl;
		}
		cin >> userinput;
		cout << "Edit Severity from 1-5 : "<< endl;
		cin >> severity;
		_symptoms.modifySymptomSeverity(cid, userinput, severity);
	}
	if(menuInput == 3){
		size = _symptoms.getNumSymptoms(cid);
		cout << "Select to update Symptom Diagnosis: " << '\n'  << endl;
		cout << '\t' <<"Symptom:" << '\t' << "Severity:" << '\t' <<"Confirmed:" << endl;
		for(int i=0; i < size; i++){
			cout << i+1 << ")" << '\t' << _symptoms.getSymptom(cid, i) << '\t' << _symptoms.getSeverity(cid, i) << '\t' << _symptoms.getConfirmed(cid, i) << endl;
		}
		cin >> userinput;
		_symptoms.modifyConfirmation(cid, userinput);
	}
	if(menuInput == 4){
		cout << "Remove a Symptom : "<< endl;
		cin >> userinput;
	}
}
/*
 * Pre: user is navigating thru other menus
 * Post: navigates user to other sub menus
 */
void enterModifyMainMenu(AllCases &_cases, AllPersons &_persons, AllSymptoms &_symptoms){
	int cid, menuInput;
	menuInput = ::printEditCaseMainMenu();
	cid = ::printViewCaseSubMenu();
		if(menuInput == 1){
			::enterCaseMenu(cid, _cases, _persons, _symptoms);
		}
		if(menuInput == 2){
			::enterPersonMenu(cid, _persons);
		}
		if(menuInput == 3){
			::enterSymptomMenu(cid, _symptoms);
		}
}
/*
 * Pre: user is navigating thru other menus
 * Post: prints all open cases
 */
void viewAllOpenCases(AllCases &_cases, AllPersons &_persons, AllSymptoms &_symptoms){
	int size =_cases.getCaseTotalNumber();
	string open = "ACTIVE";
	string contacted = "Contacted";
	string pending = "No";
	for(int i=1; i < size+1; i++){
		if(_cases.getCaseStatus(i) == 0){
			cout << "________________________________________________" << '\n' << endl;
			cout << "Person ID:         " << '\t' << _cases.getCasePid(i) << endl;
			cout << "Case ID:           " << '\t' << _cases.getCaseCid(i) << endl;
			cout << "Case Status:       " << '\t' << open << endl;
			cout << "First Name:        " << '\t' << _persons.getPersonFname(i) << endl;
			cout << "Last Name:         " << '\t' << _persons.getPersonLname(i) << endl;
			cout << "Email:             " << '\t' << _persons.getPersonEmail(i) << endl;
			cout << "Has Been Contacted:" << '\t'; //convert 0 or 1 to yes or no
			if(_cases.getCaseContacted(i) == 1) cout << contacted << endl;
			if(_cases.getCaseContacted(i) == 0) cout << pending << endl;
		}
	}
	cout << "________________________________________________" << '\n' << endl;
}
/*
 * Pre: user is navigating thru other menus
 * Post: prints identifying information of a selected case
 */
void viewACase(AllCases &_cases, AllPersons &_persons){
	int userInput = ::printViewCaseSubMenu();
	cout << "________________________________________________" << endl;
	cout << "Person ID:                " << '\t' <<_persons.getPersonID(userInput) << endl;
	cout << "Case ID:                  " << '\t' <<_cases.getCaseCid(userInput) << endl;
	cout << "Case Status               " << '\t' << _cases.getCaseStatus(userInput) << endl;
	cout << "Confirmed COVID           " << '\t' << _cases.getCaseStatus(userInput) << endl;
	cout << "Confirmed Date            ";
	_cases.getCaseDate(userInput);
	cout << "Confirmed By Employee ID: " << '\t' << _cases.getCaseWhoConf(userInput) << endl;
	cout << "________________________________________________" << endl;
	cout << "First Name:               " << '\t'  << _persons.getPersonFname(userInput) << endl;
	cout << "Last Name:                " << '\t'  << _persons.getPersonLname(userInput) << endl;
	cout << "Email:                    " << '\t'  << _persons.getPersonEmail(userInput) << endl;
	cout << "Has Been Traced:          " << '\t'  << _cases.getCaseContacted(userInput) << endl;
	cout << "________________________________________________" << endl;
}
/*
 * Pre: user is navigating thru other menus
 * Post: prints out all the untraced
 */
void listAllUncontacted(AllCases &_cases){
	cout << "list of uncontacted associates: " << endl;
	int userInput = ::printViewCaseSubMenu();
	cout << "CASE ID:     " <<_cases.getCaseCid(userInput) << endl;
	cout << "CASE STATUS: " << _cases.getCaseStatus(userInput) << '\n' << endl;
	int numAsso = _cases.getCaseNumAssociated(userInput);
	cout << "Total Associates:" << "  " << numAsso << '\n' << endl;
	if(numAsso > 0 ){
		cout << "List of Uncontacted:" << '\n' << endl;
		for(int i=0; i < numAsso; i++){
			int caseId =_cases.getCaseAssociatedList(userInput, i);
			if( _cases.getCaseContacted(caseId-1)==0){
				cout << "CASE ID:     " << _cases.getCaseAssociatedList(userInput, i) << endl;
			}
		}
	}
}
/*
 * have a hard set file
 * or user can remove comments to enter a different file. Forgot to ask
 */
int main(){
	string caseFile = "CaseFile.txt";
	string symptomFile = "SymptomFile.txt";
	//cout << "Enter a Case File: " << endl;
	//cin >> caseFile;
	//cout << "Enter a symptom file" << endl;
	//cin >> symptomFile;

	string symptomLine, caseLine;
	AllCases _cases;
	AllPersons _persons;
	AllSymptoms _symptoms;
	::scanSymptomFile(_symptoms, symptomFile);
	::scanCaseFile(_symptoms, _cases, _persons, caseFile);
	int exitLoop = 0;
	while(exitLoop == 0){
		int MainUserInput;
		MainUserInput = ::printMainMenu();
		if (MainUserInput == 1){
			::viewACase(_cases, _persons);
		}
		if (MainUserInput == 2){
			::viewAllOpenCases(_cases, _persons, _symptoms);
		}
		if (MainUserInput == 3){
			::listAllUncontacted(_cases);
		}
		if (MainUserInput == 4){
			::enterModifyMainMenu(_cases, _persons, _symptoms);
		}
		if (MainUserInput == 5){
			exitLoop = 1;
		}
	}
	return 0;
}
