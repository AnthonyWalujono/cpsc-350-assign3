#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include <exception>
#include "GenStack.h"
using namespace std;

// Returns "Delimiter syntax correct" if the [], (), {} are all matched correctly.
// Returns a string with a detailed error message otherwise.
string syntax_check(istream&);

bool should_continue();
bool get_next_file(ifstream&);

int main(int argc, const char* argv[])
{
	if (argc != 2) {
		cout << "Incorrect number of command line arguments. Aborting." << endl;
		return -1;
	}

	ifstream fin;
	fin.open(argv[1]);
	if (!fin.is_open()) {
		cout << "Unable to open file \"" << argv[1] << "\". Aborting." << endl;
		return -2;
	}

	string result = syntax_check(fin);
	cout << result << endl;

	while (result == "Delimiter syntax correct" && should_continue() && get_next_file(fin)) {
		result = syntax_check(fin);
		cout << result << endl;
	}

	return 0;
}


string syntax_check(istream& in)
{
	GenStack<char> stack;
	ostringstream oss;
	char c;
	unsigned line_no = 1;
	const string left_delims = "({[";
	const string right_delims = ")}]";

	while (in.get(c)) {
		if (c == '\n') {
			line_no++;
		} else if (left_delims.find_first_of(c) != string::npos) {
			stack.Push(c);
		} else {
			size_t pos = right_delims.find_first_of(c);

			if (pos != string::npos) {
				//Detect right Delimiter but stack is empty
				if (stack.isEmpty()) {
					oss << "Line " << line_no << ": Unexpected " << c;
					return oss.str();
				}
				////Detect mismatch Delimiter
				else if (stack.peek() != left_delims[pos]) {
					oss << "Line " << line_no << ": Expected "
						<< right_delims[left_delims.find_first_of(stack.peek())]
						<< " and found " << c;
					return oss.str();
				} else {
					stack.pop();
				}
			}
		}
	}
	//Reach end of file but stack is not empty.
	if (!stack.isEmpty()) {
		oss << "Reached end of file: missing "
			<< right_delims[left_delims.find_first_of(stack.peek())];
		return oss.str();
	}

	return "Delimiter syntax correct";
}

bool should_continue()
{
	char c, extra;
	bool invalid;

	do
	{
		invalid = false;

		cout << "Do you want to analyze another file (Y/N)? ";
		cin >> c;	// Get the first nonwhitespace letter
		c = toupper(c);

		if (c != 'Y' && c != 'N') {
			invalid = true;
		}

		// Check to make sure they didn't type any other nonwhitespace character
		while (cin.get(extra) && extra != '\n') {
			if (!isspace(extra)) {
				invalid = true;
			}
		}

		if (invalid) {
			cout << "Invalid entry" << endl;
		}

	} while (invalid);

	return (c == 'Y');
}


bool get_next_file(ifstream& fin)
{
	fin.close();
	//ask is user want to enter new file
	cout << "Enter the name of the file you want to analyze (no quotes): ";
	string filename;
	getline(cin, filename);
	fin.open(filename);

	if (!fin.is_open()) {
		cout << "Unable to open file \"" << filename << "\". Aborting." << endl;
		return false;
	}
	return true;
}
