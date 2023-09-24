#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>

using namespace std;

const int MAX_EXPRESSION_SIZE = 65, LETTER_OFFSET_IN_ASCII = 32;

enum Menu {
	PRINT_TO_FILE_AND_SCREEN = 1, QUIT = 2
};

class Stack {
	public:
		Stack() { InitializeStack(); }

		void InitializeStack() { stackTop = 0; }

		bool IsEmpty() const { return (stackTop == 0); }

		bool IsFullStack() const { return (stackTop == MAX_EXPRESSION_SIZE); }

		void Push(char);

		char Top() const;

		void Pop();

		int GetStackSize() const { return stackTop; }

		string ToString();
	private:
		char expression[MAX_EXPRESSION_SIZE];
		int stackTop;
};

void ClearInvalidInput(string errMsg);

void PrintToFileAndScreen(string inFileName, string outFileName, string border, string header);

//void PrintToFile(ofstream& outFil, string original, string reversed);

//void PrintToScreen(string original, string reversed);

string ProcessString(string);

string ToLower(string);

void CreateStringStack(Stack&, string);

int main() {
	int userChoice;
	string inFileName = "Test_Data.txt", outFileName = "OutputFile.txt",
		border, header;
	stringstream headerSS, borderSS;

	borderSS << setfill('-') << setw((MAX_EXPRESSION_SIZE + 1) * 2) << "\n";
	headerSS << left << setw(MAX_EXPRESSION_SIZE + 1) << "INPUT" << setw(MAX_EXPRESSION_SIZE + 1) << "REVERSED";

	border = borderSS.str();
	header = headerSS.str();

	cout << left;

	do {
		cout << "\n\nMenu:\n"
			"1. Print expressions to a file and screen\n"
			"2. Quit\n";
		cin >> userChoice;

		switch (userChoice) {
		case PRINT_TO_FILE_AND_SCREEN:
			PrintToFileAndScreen(inFileName, outFileName, border, header);
		break;
		case QUIT:
			cout << "QUITTING ..." << endl;
			break;
		default:
			ClearInvalidInput("INVALID INPUT");
		}
		
	} while (userChoice != QUIT);

}

string Stack::ToString() {
	stringstream ss;
	int size = stackTop;
	for (int i = 0; i < size; i++) {
		ss << Top();
		Pop();
	}
	ss << setw(MAX_EXPRESSION_SIZE);
	return ss.str();
}


void Stack::Push(char newChar) {
	if (!IsFullStack()) {
		expression[stackTop] = newChar;
		stackTop++;
	}
	else {
		cout << "Push Failed, Stack is full\n";
	}
}

char Stack::Top() const {
	if (!IsEmpty()) {
		return expression[stackTop - 1];
	}
}

void Stack::Pop() {
	if (!IsEmpty()) {
		stackTop--;
	}
	else {
		cout << "Cannot pop from an empty stack\n";
	}
}

void ClearInvalidInput(string errMsg) {
	cout << "\n" << errMsg << "\n";
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void PrintToFileAndScreen(string inputFileName, string outputFileName, string border, string header) {
	ifstream inputFile(inputFileName);
	ofstream outFile(outputFileName);
	string tempString, reversedString;
	Stack tempStack;

	if (!inputFile) {
		cout << "Input file not found. Exiting the program." << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
	if (inputFile.peek() == EOF) {
		cout << "The input file is empty. Quitting the program." << endl;
		inputFile.close();
		system("pause");
		exit(EXIT_FAILURE);
	}

	outFile << left << header << "\n";
	cout << border << header << "\n";

	while (!inputFile.eof()) {
		getline(inputFile, tempString);
		if (tempString.length() <= MAX_EXPRESSION_SIZE) {
			CreateStringStack(tempStack, tempString);
			reversedString = tempStack.ToString();

			//prints to file
			outFile << setw(MAX_EXPRESSION_SIZE + 1) << tempString
				<< setw(MAX_EXPRESSION_SIZE) << reversedString << "\n";

			//prints to screen
			cout << setw(MAX_EXPRESSION_SIZE + 1) << tempString
				<< setw(MAX_EXPRESSION_SIZE) << reversedString << "\n";
		}

	}
	cout << border;
	inputFile.close();
	outFile.close();
}

//void PrintToFile(ofstream& outFile, string expression, string reversedExpression) {
//
//	outFile << setw(MAX_EXPRESSION_SIZE) << expression
//		<< setw(MAX_EXPRESSION_SIZE) << reversedExpression << "\n";
//
//}

//void PrintToScreen(string original, string reversed) {
//	cout << setw(MAX_EXPRESSION_SIZE) << original
//		<< setw(MAX_EXPRESSION_SIZE) << reversed << "\n";
//}

void CreateStringStack(Stack& stack, string expression) {
	expression = ToLower(expression);
	expression = ProcessString(expression);

	int strLen = expression.length();

	for (int i = 0; i < strLen; i++) {
		stack.Push(expression[i]);
	}

}

string ProcessString(string str) {
	string processedString = "";
	int strLen = str.length();
	for (int i = 0; i < strLen; i++) {
		char ch = str[i];
		if (((ch >= 'a') && (ch <= 'z'))) {
			processedString += ch;
		}
		else if (ch == '\'') { //skips letter after apostrophe
			i++;
		}
	}
	return processedString;
}

string ToLower(string str) {
	string lowerCaseStr = "";
	for (int i = 0; i < str.length(); i++) {
		char ch = str[i];
		if (((ch >= 'A') && (ch <= 'Z'))) {
			ch += LETTER_OFFSET_IN_ASCII; //converts char to lower case
		}
		lowerCaseStr += ch;
	}
	return lowerCaseStr;
}
