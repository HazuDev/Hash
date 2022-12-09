#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

template <typename T>
class proccess {
private:
	T path;
	T selected;

public:
	void constructor(T n_path) {
		this->path = n_path;
	}

	void initProccess(T* ptr) {
		ifstream myFile(path);

		if (myFile.is_open()) {
			getline(myFile, *ptr, '\0');
			myFile.close();
		}
	}

	void execute(string cmd) {
		if (cmd.rfind("print: ", 0) == 0) {
			string check = "print: ";
			cout << cmd.substr(check.length(), (cmd.length() + 1)) << endl;
		}

		else if (cmd.rfind("mkFile: ", 0) == 0) {
			string check = "mkFile: ";
			string fileName = cmd.substr(check.length(), (cmd.length() + 1));

			ofstream myFile(fileName);
			myFile.close();
		}

		else if (cmd.rfind("select: ", 0) == 0) {
			string check = "select: ";
			string fileName = cmd.substr(check.length(), (cmd.length() + 1));

			this->selected = fileName;
		}

		else if (cmd.rfind("write: ", 0) == 0) {
			string check = "write: ";
			string content = cmd.substr(check.length(), (cmd.length() + 1));

			ofstream myFile(selected);
			
			if (myFile.is_open()) {
				myFile << content;
				myFile.close();
			}
		}
	}
};

static void init(string path) {
	string content;
	string* ptr = &content;

	proccess<string> myProccess;
	myProccess.constructor(path);
	myProccess.initProccess(ptr);

	stringstream ss(content);
	string check;

	while (getline(ss, check, '\n')) {
		myProccess.execute(check);
	}

	ptr = NULL;
	delete ptr;
}

int main(void) {
	string path;

	cout << "> File : ";
	cin >> path;

	init(path);

	return 0;
}