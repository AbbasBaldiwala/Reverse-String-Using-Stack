#include <iostream>
#include <sstream>
#include <limits>

using namespace std;

const int MAX_EXPRESSION_SIZE = 65;

enum Menu {
	PRINT_TO_FILE_AND_SCREEN = 1, QUIT = 2
};

class Stack {
	public:
		Stack();

		void setExpression();

		string ToString();
	private:
		string original, reversed;
};

void ClearInvalidInput(string errMsg);

int main() {
	int userChoice;

	do {
		cout << "\n\nMenu:\n"
			"1. Print expressions to a file and screen\n"
			"2. Quit\n";
		cin >> userChoice;

		switch (userChoice) {
		case PRINT_TO_FILE_AND_SCREEN:

		break;
		case QUIT:
			cout << "QUITTING ..." << endl;
			break;
		default:
			ClearInvalidInput("INVALID INPUT");
		}
		
	} while (userChoice != QUIT);

}

void ClearInvalidInput(string errMsg) {
	cout << "\n" << errMsg << "\n";
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}