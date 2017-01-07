#include <string>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

int main(){
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

	cout << "\nWriting file...\n";

	file << "#include <stdio.h>\n#include <iostream>\nusing namespace std;\n";
	file << "\nint main(){\n";
	file << "uint8_t cells[512] = {0};\nuint8_t *ptr = cells;\n";

	for(char &c : command){
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
			file << "\t*ptr = getchar();\n";
		} else if(c == '['){
			file << "\twhile (*ptr) {\n";
		} else if(c == ']'){
			file << "\t}\n";
		}
	}
	if(cell_bug == 'y'){
		file << "\tfor(int i = 0; i < " << numberOfCells * 4 << "; i += 4){\n\t\tcout << (int) (cells[i]) << \" \";\n\t\tcout << (int) (cells[i+1]) << \" \";\n\t\tcout << (int) (cells[i+2]) << \" \";\n\t\tcout << (int) (cells[i+3]) << \"\\n\";\n\t}\n";
	}
	file << "}";
	file.close();
	cout << "Do you want to compile? [y/n] ";
	char te;
	cin >> te;
	if(te == 'y'){
		system(("g++ -o " + name + ".exe" + " " + name + ".cpp").c_str());
	}
	return 0;
}

