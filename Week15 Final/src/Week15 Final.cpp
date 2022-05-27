//============================================================================
// Name        : Week15.cpp
// Author      : luis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {
	class Stuff{
	private:
	    int x[3];
	public:
	    Stuff(){
			for (int i=0; i<3; i++){
				x[i] = 0;
			}
		}
	Stuff& operator+ (const Stuff& b){

		return b;
	}

	// pre: none
	// post: A stuff object is returned that contains an array where
	// each element of the array is the sum of the implicit
	// argument's parallel array value plus the explicit argument's
	// parallel array value.

	};

}
