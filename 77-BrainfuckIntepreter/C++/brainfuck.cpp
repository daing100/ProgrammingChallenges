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
	ofstream file;
	file.open(name + ".cpp");
	cout << "Enter the command: ";
	char command[16384] = {0};
	cin >> command;
	cout << "\nWriting file...\n";

	file << "#include <stdio.h>\n#include <iostream>\nusing namespace std;\n";
	file << "\nint main(){\n";
	file << "uint8_t cells[512] = {0};\nuint8_t *ptr = cells;\n";

	for(char &c : command){
		if(c == '>') {
			file << "++ptr;\n";
		} else if(c == '<'){
			file << "--ptr;\n";
		} else if(c == '+'){
			file << "++*ptr;\n";
		} else if(c == '-'){
			file << "--*ptr;\n";
		} else if(c == '.'){
			file << "putchar(*ptr);\n";
		} else if(c == ','){
			file << "*ptr = getchar();\n";
		} else if(c == '['){
			file << "while (*ptr) {\n";
		} else if(c == ']'){
			file << "}\n";
		}
	}
	file << "for(int i = 0; i < 128; i += 4){cout << (int) (cells[i]) << \" \";cout << (int) (cells[i+1]) << \" \";cout << (int) (cells[i+2]) << \" \";cout << (int) (cells[i+3]) << \"\\n\";}\n";
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

