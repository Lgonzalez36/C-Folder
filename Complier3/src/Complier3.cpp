#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
using namespace std;

// You will need these forward references.
class Expr;
class Stmt;

// Runtime Global Variables
int pc;  				// program counter
vector<string> lexemes;
vector<string> tokens;
vector<string>::iterator lexitr;
vector<string>::iterator tokitr;
map<string, int> vartable; 	// map of variables and their values
vector<Stmt*> insttable; 		// table of instructions
map<string, string> symboltable; // map of variables to datatype (i.e. sum t_integer)



// You may need a few additional global methods to manipulate the global variables


// Classes Stmt and Expr
// It is assumed some methods in statement and expression objects will change and
// you may need to add a few new ones.

class Expr{ // expressions are evaluated!
	//abstract base class
public:
	virtual int eval() = 0;
	virtual string toString() = 0;
	virtual ~Expr(){}
};

class ConstExpr : public Expr{
private:
	int value;
public:
	/*****************************************************/
	ConstExpr(int val) : value(val){}
	int eval(){return value;}
	string toString(){
		string temp;
		temp = to_string(value);
		return temp;
	}
};

class IdExpr : public Expr{
private:
	string id;
public:
	/***********************************************************/
	IdExpr(string s) : id(s){}
	int eval(){return vartable[id];}
	string toString(){return id;}
};

class InFixExpr : public Expr{
private:
	vector<Expr *> exprs;
	vector<string> ops;  // tokens of operators
public:
	/***********************************************************/
	InFixExpr(){}
	~InFixExpr(){
		for (int i=0; i<exprs.size(); i++)
			delete exprs[i];
	}
	int eval(){}
	string toString(){}
};

class Stmt{ // statements are executed!
private:
	string name;
public:
	Stmt(){}
	Stmt(string s): name(s){}
	virtual ~Stmt(){};
	virtual string toString() = 0;
	virtual void execute() = 0;
};

class AssignStmt : public Stmt{
private:
	string var;
	Expr* p_expr;
public:
	AssignStmt(string id, Expr* p): Stmt("s_assign"), var(id), p_expr(p){}
	~AssignStmt(){}
	string toString(){
		string s = "s_assign" + var + " " + p_expr->toString();
		return s;
	}
	void execute(){
		vartable[var] = p_expr->eval();
	}
};

class InputStmt : public Stmt{
private:
	string var;
public:
	InputStmt(){}
	~InputStmt(){}
	string toString(){}
	void execute(){}
};
class StrOutStmt : public Stmt{
private:
	string value;
public:
	StrOutStmt(){}
	~StrOutStmt(){}
	string toString(){}
	void execute(){}
};

class ExprOutStmt : public Stmt{
private:
	Expr* p_expr;
public:
	ExprOutStmt(){}
	ExprOutStmt(Expr* t):p_expr(t){}
	~ExprOutStmt(){}
	string toString(){
		string s = "t_exprout" + p_expr->toString();
		return s;
	}
	void execute(){}
};

class IfStmt : public Stmt{
private:
	Expr* p_expr;
	int elsetarget;
public:
	IfStmt(Expr* p, int et):Stmt ("t_if"), p_expr(p), elsetarget(et){}
	~IfStmt(){}
	string toString(){
		string s = "t_if" + p_expr->toString() + " " + to_string(elsetarget);
		return s;
	}
	void execute(){

	}
};

class WhileStmt : public Stmt{
private:
	Expr* p_expr;
	int elsetarget;
public:
	WhileStmt(Expr* p, int et):Stmt ("t_while"), p_expr(p), elsetarget(et){}
	~WhileStmt(){}
	string toString(){
		string t = to_string(elsetarget);
		string s = "t_while" + p_expr->toString() + " " + t;
		return s;
	}
	void execute(){}
};

class Compiler{
private:
	void buildIf(){
		//else target
		int et = 0; //fix
		//move past
		tokitr++; lexitr++;
		tokitr++; lexitr++;
		//build expression
		Expr* t = buildExpr();
		insttable.push_back(new IfStmt(t,et));

	}
	void buildWhile(){
		//build else target
		int et = 0; //fix else target
		//move past
		tokitr++; lexitr++;
		tokitr++; lexitr++;
		//build expression
		Expr* t = buildExpr();
		insttable.push_back(new WhileStmt(t,et));
	}
	//void buildStmt();
	void buildAssign(){
		// store variables
		string var = *lexitr;
		// move past =
		tokitr++;lexitr++;
		tokitr++;lexitr++;
		// build expression
		Expr* t = buildExpr();
		insttable.push_back(new AssignStmt(var,t));
	}
	void buildInput(){
		//move past
		tokitr++; lexitr++;
		tokitr++; lexitr++;
	}
	void buildOutput(){
		tokitr++; lexitr++;
		tokitr++; lexitr++;
		// build expression
		Expr* t = buildExpr();
		insttable.push_back(new ExprOutStmt(t));

	}
	// use one of the following buildExpr methods
	//void buildExpr(Expr*&);
	/***************************************************/
	Expr* buildExpr(){
		Expr* eptr;
		// only works for const and id expressions
		if(*tokitr == "t_id")
			eptr = new IdExpr(*lexitr);
		else
			eptr = new ConstExpr(stoi(*lexitr));
		//move past semicolon
		tokitr++; lexitr++;
		tokitr++; lexitr++;
		return eptr;
	}

	// headers for populate methods may not change
	void populateTokenLexemes(istream& infile){
		 string tok, lex;
		 infile >> tok >> lex;
		 while(!infile.eof()){
			cout << tok << " " << lex << endl;
			tokens.push_back(tok);
			lexemes.push_back(lex);
			infile >> tok >> lex;
		}
		tokitr = tokens.begin();
		lexitr = lexemes.begin();
	}
	void populateSymbolTable(istream& infile){
		string var, type;
		infile >> var >> type;
		while (!infile.eof()){
			cout << var << " " << type << endl;
			symboltable[var] = type;
			infile >> var >> type;
		}
	}
public:
	// headers may not change
	Compiler(istream& source, istream& symbols){
		populateTokenLexemes(source);
		populateSymbolTable(symbols);
	}
	// The compile method is responsible for getting the instruction
	// table built.  It will call the appropriate build methods.
	bool compile(){
		string type, var;
		// traverse tokens (vars part) to build vartable
		tokitr = tokens.begin();
		lexitr = lexemes.begin();
		if (*tokitr == "t_var"){  // there are variables to process
			tokitr++; lexitr++;
			do{
				if (*tokitr == "t_integer"){
					type = "t_integer";
					tokitr++; lexitr++;
					vartable[*lexitr] = 0;
				}
				else if (*tokitr == "t_string"){
					type = "t_string";
					tokitr++; lexitr++;
				//	vartable[*lexitr] = "";
				}
				else if (*tokitr == "t_id"){ // chained variable list
					if (type == "t_integer"){
						vartable[*lexitr] = 0;
					}
				//	else vartable[*lexitr] = "";
				}
				tokitr++, lexitr++;   // move past processed var or ; or ,
			}while (*tokitr != "t_main");
			tokitr++; lexitr++;  // move past main
		}
		// traverse tokens (stmtlist part) to build statements
		for (; tokitr != tokens.end(); tokitr++, lexitr++){
			cout << "stmtlist " << *tokitr << endl;
			if (*tokitr == "t_if"){
				buildIf();
			}
			else if (*tokitr == "t_id"){
				buildAssign();
			}
			else if (*tokitr == "t_while"){
				buildWhile();
			}
			else if (*tokitr == "t_input"){
				buildInput();
			}
			else if (*tokitr == "t_output"){
				buildOutput();
			}
		}
	}
	// The run method will execute the code in the instruction
	// table.
	void run(){
		// performs a simple sequential scan of the insttable object
				pc = 0;
				while (pc < insttable.size()){
					cout << "executing instruction " + to_string(pc) << endl;
					insttable[pc]->execute();
					pc++;
				}
			}
};

// Runtime Global Methods
void dump(){ 				// prints vartable, instable, symboltable
	cout << endl;
	cout << "token and lexeme vectors" << endl;
	for (tokitr = tokens.begin(), lexitr = lexemes.begin();
			tokitr != tokens.end();
			tokitr++, lexitr++){
		cout << *tokitr << " " << *lexitr << endl;
	}
	cout << endl;
	cout << "symbol table" << endl;
	for (map<string, string>::iterator mitr = symboltable.begin();
			mitr != symboltable.end();
			mitr++){
		cout << mitr->first << " " << mitr->second << endl;
	}
	cout << endl;
	cout << "var table" << endl;
	for (map<string, int>::iterator mitr = vartable.begin();
			mitr != vartable.end();
			mitr++){
		cout << mitr->first << " " << mitr->second << endl;
	}
	cout << "instruction table" << endl;
	for (vector<Stmt*>::iterator vitr = insttable.begin();
			vitr != insttable.end();
			vitr++){
		cout << (*vitr)->toString() << endl;
	}
}

int main(){
	ifstream infile1("source2.txt");
	ifstream infile2("symbol1.txt");
	if (!infile1 || !infile2) exit(-1);
	Compiler c(infile1, infile2);
	c.compile();
	dump();
	c.run();
	return 0;
}

