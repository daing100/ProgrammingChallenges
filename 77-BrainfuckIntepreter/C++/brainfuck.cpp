#include <string>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

int main(){ // is very inefficient
	cout << "Enter name of code file (no ext): ";
	string name;
	cin >> name;
	cout << "Include cells at the end of the program? [y/n] ";
	char cell_bug;
	cin >> cell_bug;
	int numberOfCells;
	if(cell_bug == 'y'){
		cout << "How many sets of 4 cells will be shown? (max 4096)\nInput: ";
		cin >> numberOfCells;
	}
	ofstream file;
	file.open(name + ".cpp");
	cout << "\nEnter the command: ";
	char command[16384] = {0};
	cin >> command;


	cout << "\nPrint command at the end of the program? [y/n] ";
	char keepCommand;
	cin >> keepCommand;

	cout << "\nWriting file...\n";

	file << "#include <stdio.h>\n#include <iostream>\nusing namespace std;\n";
	file << "\nint main(){\n";
	file << "uint8_t cells[512] = {0};\nuint8_t *ptr = cells;\n";

	if(keepCommand == 'y'){
		file << "char command[] = \"" << command << "\";\n";
	}

	int indentCounter = 0;

	for(char &c : command){
		for (int i = 0; i < indentCounter; i++){
			file << "\t";
		}
		if(c == '>') {
			file << "\t++ptr;\n";
		} else if(c == '<'){
			file << "\t--ptr;\n";
		} else if(c == '+'){
			file << "\t++*ptr;\n";
		} else if(c == '-'){
			file << "\t--*ptr;\n";
		} else if(c == '.'){
			file << "\tputchar(*ptr);\n";
		} else if(c == ','){
			file << "\t*ptr = getchar();\n\tgetchar(); // To take the newline that appears after entering a char.\n";
		} else if(c == '['){
			indentCounter++;
			file << "\twhile (*ptr) {\n";
		} else if(c == ']'){
			indentCounter--;
			file << "}\n";
		}
	}
	if(cell_bug == 'y'){
		file << "\tfor(int i = 0; i < " << numberOfCells * 4 << "; i += 4){\n\t\tcout << (int) (cells[i]) << \" \";\n\t\tcout << (int) (cells[i+1]) << \" \";\n\t\tcout << (int) (cells[i+2]) << \" \";\n\t\tcout << (int) (cells[i+3]) << \"\\n\";\n\t}\n";
	}
	if(keepCommand == 'y'){
		file << "\tcout << command;\n";
	}
	file << "}";
	file.close();
	cout << "Do you want to compile? [y/n] ";
	char te;
	cin >> te;
	if(te == 'y'){
		system(("g++ -o " + name + ".exe" + " " + name + ".cpp").c_str());
		cout << "Run now? [y/n] ";
		char ans;
		cin >> ans;
		if(ans == 'y'){
			system((name + ".exe").c_str());
		}
	}

	return 0;
}

