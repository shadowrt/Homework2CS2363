//============================================================================
// Name        : Homework2PostFixCalcCS2363.cpp
// Author      : R. Bruce Tuckey    SP19-CS2363-TS02S
// Version     :
// Copyright   : Dr. Goulden         Mon 5:30-8:00
// Description : Postfix calculator
// Write a program that accepts a string that is a space-delimited arithmetic expression
// in postfix notation. Use a vector to compute the value.
// This problem has an extra twist. The string contains characters, so 10 isn’t a ten,
// but is the char 1 followed by the char 0. You will need to convert string representations
// of integers (signed and unsigned) into their integer values. You’ll also need to handle
// unary – and +.
//============================================================================

#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool validInput(string localExpression);
// very basic checking that you have input proper symbols and numbers with spaces
// not checking order or anything else as guideline says to assume proper input format
// this only checks for a "fatfinger" situation (ie invalid characters).
// @param localExpression your input string
// @return boolean if it's valid calculator input

bool isNumber(char myChar);
// make sure its number
// @params myChar is the character we are processing
// @return boolean if its a valid integer number

void processExpression(string myExpr);
// This section got nasty looking so a made some support functions
// maybe this isnt a grest use of switch, it just seemed like I needed to do something other than if's
// @params myExpr is the string the user has entered as an equation
// @return - nothing output in this fuction gives the result.

int main() {
	string theExpression = "k";											// initialize to enter while loop
	cout << "Welcome to postfix calculator enter 0 to exit." << endl;	// Nice prompt
	while (theExpression != "0") {										// start your while loop
		cout << "Enter your expression: ";								// prompt for input
		getline(cin, theExpression);									// accept input
		if (validInput(theExpression) == true && theExpression != "0") {	// basic char check and not 0 to exit
			processExpression(theExpression);							// go process the equation & show result
		}
		else if (theExpression != "0") {									// some random char was in that
			cout << "Ya, I don't know what to do with: " << theExpression << endl;	// whine at them
		}
	}
	// Ya, We're done, later.
	cout << "Thank you for using postfix calculator..  ;) " << endl;
	cout << "Copyright 2019 LoneGentProductions.com" << endl;
	return 0;
}

void processExpression(string myExpr) {
	vector<int> myStack;									// create a int vector to use
	int realNumber;											// have a real number var to push
	string myNum;											// a string to use while parsing input
	for (unsigned int i = 0; i < myExpr.size(); i++) {			// walk the expression
		if ((myExpr[i] == '+' || myExpr[i] == '-') && myExpr[i + 1] != ' ' && (i + 1) != myExpr.size()) {
			// this is the sign or a number
			myNum += myExpr[i];								// build number - this is for unaries
		}
		else if (isNumber(myExpr[i]) == true) {				// its a number
			myNum += myExpr[i];								// build number - this one is real number
		}
		else if (myExpr[i] == ' ') {							// thats the end of a number push on the stack/vector
			realNumber = stoi(myNum);						// convert to integer
			myStack.push_back(realNumber);					// push it on the stack/vector
			myNum = "";										// reset the number dummy!!!!
		}
		else {												// time to do the math
			switch (myExpr[i]) {								// use the character should only be operator
			case '-': {										// do subtraction and push
				realNumber = ((myStack[myStack.size() - 2]) - (myStack[myStack.size() - 1]));
				myStack.pop_back();							// clear first number
				myStack.pop_back();							// clear second number
				myStack.push_back(realNumber);				// push the current value
				i++;										// artificially pass the space after operator
			}; break;
			case '+': {										// do addition and push
				realNumber = ((myStack[myStack.size() - 2]) + (myStack[myStack.size() - 1]));
				myStack.pop_back();							// clear first number
				myStack.pop_back();							// clear second number
				myStack.push_back(realNumber);				// push the current value
				i++;										// artificially pass the space after operator
			}; break;
			case '/': {										// do division and push
				realNumber = ((myStack[myStack.size() - 2]) + (myStack[myStack.size() - 1]));
				myStack.pop_back();							// clear first number
				myStack.pop_back();							// clear second number
				myStack.push_back(realNumber);				// push the current value
				i++;										// artificially pass the space after operator
			}; break;
			case '*': {										// do multiplication and push
				realNumber = ((myStack[myStack.size() - 2]) * (myStack[myStack.size() - 1]));
				myStack.pop_back();							// clear first number
				myStack.pop_back();							// clear second number
				myStack.push_back(realNumber);				// push the current value
				i++;										// artificially pass the space after operator
			}; break;
			case '%': {										// do modulous and push
				realNumber = ((myStack[myStack.size() - 2]) % (myStack[myStack.size() - 1]));
				myStack.pop_back();							// clear first number
				myStack.pop_back();							// clear second number
				myStack.push_back(realNumber);				// push the current value
				i++;										// artificially pass the space after operator
			}; break;
			}
		}
	}
	cout << "Your number is: " << myStack[myStack.size() - 1] << endl;
	myStack.clear();										// ensure you cleanup
	return;
}

bool validInput(string localExpression) {
	string validInput = "0123456789+-*/% ";						// a list of valid numbers
	int goodTxt = 0;											// no matches to start
	for (unsigned int i = 0; i < localExpression.size(); i++) {	// walk through their input
		for (unsigned int v = 0; v < validInput.size(); v++) {	// walk the valid input string
			if (validInput[v] == localExpression[i]) {			// check the match
				goodTxt++;										// we got a good digit
			}
		}
	}
	if (goodTxt != localExpression.size())
		return false;									// Nope, there's something jenky with your input
	else
		return true;									// Yes it's good input
}

bool isNumber(char myChar) {
	string validNumbers = "0123456789"; 				// valid integers
	bool myBoo = false;									// set to false so we have single exit for true
	for (unsigned int v = 0; v < validNumbers.size(); v++) {		// walk through the valid numbers
		if (myChar == validNumbers[v]) {					// It is a real number
			myBoo = true;								// set it true
		}
	}
	return myBoo;										// these are/are not the droids we're looking for
}
