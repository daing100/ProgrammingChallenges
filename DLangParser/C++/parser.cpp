#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#define VERSION 1.4


void split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void printHelp(){
	std::cout << "DLang to C++ parser v" << VERSION << "\nArguments are:\n";
	std::cout << "  -i arg        Designates the input file as \"arg\".\n";
	std::cout << "  -o arg        Designates the output cpp file as \"arg\".\n";
	std::cout << "  -h            Displays this message. Skips everything else.\n";
	std::cout << "  -rm           Removes the cpp file upon compilation.\n";
	std::cout << "  -dc           Disables automatic compilation.\n";
	std::cout << "  -uspc         Makes the delimiter space. Makes strings difficult.\n";
	std::cout << "  -cdlm arg     Makes 'arg' the delimiter.\n";
}

void printVersion(){
	std::cout << "DLang to C++ parser\n    v" << VERSION << " by Carl-Fredrik Lidgren";
}

int main(int argc, char *argv[]){
	std::string ifile;
	std::string ofile = "temp.txt";

	bool copyfile = 0;
	bool removeFile = 0;
	bool notHelp = 1;
	bool compile = 1;
	char delim_ = ':';

	if(argc > 1){
		for(int i = 1; i < argc; i++){
			std::string temp(argv[i]);
			if(temp == "-h" || temp == "--help"){
				printHelp();
				return 0;
			} else if(temp == "-o"){
				ofile = argv[i+1];
				i++;
			} else if(temp == "-i"){
				ifile = argv[i+1];
				i++;
			} else if(temp == "-c"){
				copyfile = 1;
			} else if(temp == "-rm"){
				removeFile = 1;
			} else if(temp == "-dc"){
				compile = 0;
			} else if(temp == "-uspc" || "--use-space-as-delim"){
				delim_ = ' ';
			} else if(temp == "-cdlm" || "--custom-delim"){
				delim_ = argv[i+1][0];
				i++;
			} else if(temp == "-v" || "--version"){
				printVersion();
				return 0;
			} else {
				std::cout << "Unrecognized command\n";
				printHelp();
			}
		}
	} else {
		printHelp();
		notHelp = 0;
	}
	if(notHelp){
		int linecount = 0;

		std::string line;
		std::ifstream file(ifile);
		for(linecount = 0; std::getline(file, line); linecount++);
		file.clear();
		file.seekg(0, file.beg);
		std::vector<std::string> stringVec(linecount);
		std::ofstream outfile(ofile);
		for(size_t i = 0; i < stringVec.size(); i++){
			std::getline(file, line);
			stringVec[i] = line;
			if(copyfile) outfile << stringVec[i] << std::endl;
		}

		std::vector<std::string> container;
		if(!copyfile){
			outfile << "#include <iostream>\n#include <stdlib.h>\n#include <string>\n#include <vector>\n\nusing namespace std;\n\n";
			outfile << "int std_var = 0;\nint *b = &std_var;\nstring std_str = \"\";\nstring *c = &std_str;\n\n";
			outfile << "int main(){\n";

			int ifs = 0;
			int elses = 0;
			int total_ifs = 0;

			for(size_t i = 0; i < stringVec.size(); i++){

				container = split(stringVec[i], delim_);

				bool else_check = elses > 0;

				if(ifs > 0){
					if(container[ifs - 1] != "then"){
						--ifs;
						outfile << "}" << std::endl;
					}
				}

				std::cout << container[ifs+elses] << " : " << ifs+elses << std::endl;

				// Basic functionality
				if(container[ifs+elses] == "make"){
					outfile << container[ifs+elses+1] << " " << container[ifs+elses+2] << " = " << container[ifs+elses+3] << ";" << std::endl;
				}
				else if(container[ifs+elses] == "use"){
					outfile << "b = &" << container[ifs+elses+1] << ";" << std::endl;
				}
				else if(container[ifs+elses] == "<<<"){
					outfile << container[ifs+elses+1] << ":" << std::endl;
				}
				else if(container[ifs+elses] == ">>>"){
					outfile << "goto " << container[ifs+elses+1] << ";" << std::endl;
				}
				else if(container[ifs+elses] == "="){
					outfile << "*b = " << container[ifs+elses+1] << ";" << std::endl;
				}
				
				// Arithmetic
				
				else if(container[ifs+elses] == "+"){
					outfile << "*b += " << container[ifs+elses+1] << ";" << std::endl;
				}
				else if(container[ifs+elses] == "+="){
					outfile << "*b = " << container[ifs+elses+1] << " + " << container[ifs+elses+2] << ";" << std::endl;
				}
				else if(container[ifs+elses] == "-") {
					outfile << "*b -= " << container[ifs+elses+1] << ";" << std::endl;
				}
				else if(container[ifs+elses] == "-="){
					outfile << "*b = " << container[ifs+elses+1] << " - " << container[ifs+elses+2] << ";" << std::endl;
				}
				else if(container[ifs+elses] == "*") {
					outfile << "*b *= " << container[ifs+elses+1] << ";" << std::endl;
				}
				else if(container[ifs+elses] == "*="){
					outfile << "*b = " << container[ifs+elses+1] << " * " << container[ifs+elses+2] << ";" << std::endl;
				}
				else if(container[ifs+elses] == "/") {
					outfile << "*b /= " << container[ifs+elses+1] << ";" << std::endl;
				}
				else if(container[ifs+elses] == "/="){
					outfile << "*b = " << container[ifs+elses+1] << " / " << container[ifs+elses+2] << ";" << std::endl;
				}
				
				// I/O stuff
				
				else if(container[ifs+elses] == "say") {
					outfile << "cout << *b;" << std::endl;
				}
				else if(container[ifs+elses] == "sayc") {
					outfile << "cout << *c;" << std::endl;
				}
				else if(container[ifs+elses] == "sayv"){
					//std::cout << "--\n" << ifs << std::endl << elses << "\n--" << std::endl;
					outfile << "cout";
					for (size_t j = ifs + elses; j < container.size()-1; j++){
						outfile << " << " << container[j+1];
					}
					outfile << ";" << std::endl;
				} else if(container[ifs+elses] == "listen") {
					outfile << "cin >> *c;" << std::endl;
				}
				else if(container[ifs+elses] == "listenv") {
					outfile << "cin >> " << container[ifs+elses+1] << ";" << std::endl;
				}
				else if(container[ifs+elses] == "stn") {
					outfile << "*b = stoi(*c, nullptr, 10);" << std::endl;
				}
				
				// Array/Vector stuff
				
				else if(container[ifs+elses] == "array") {
					outfile << "vector<" << container[ifs+elses+1] << "> " << container[ifs+elses+2] << "(" << container[ifs+elses+3] << ");" << std::endl;
				}

				// Conditional stuff
				
				else if(container[ifs+elses] == "if"){
					++total_ifs;
					// std::cout << container[ifs+elses+1] << "\n" << container[ifs+elses+2] << std::endl;
					outfile << "bool t_" << total_ifs << " = (*b " << container[ifs+elses+1] << " " << container[ifs+elses+2] << ");" << std::endl;
					outfile << "if(t_" << total_ifs << "){" << std::endl;
					++ifs;
				} else if(container[ifs+elses] == "ife"){
					++total_ifs;
					outfile << "bool t_" << total_ifs << " = (*b " << container[ifs+elses+1] << " " << container[ifs+elses+2] << " == " << container[ifs+elses+3] << ");" << std::endl;
					outfile << "if(t_" << total_ifs << "){" << std::endl;
					++ifs;
				} else if(container[ifs+elses] == "else"){
					outfile << "else {" << std::endl;
					elses++;
					i--;
				}

				if(else_check && elses > ifs){
					outfile << "}" << std::endl;
					elses--;
					i--;
				}
			}
		}
		outfile << "return 0;\n}";

		file.close();
		outfile.close();

		if(!copyfile && compile){
			system(("g++ -o " + ofile.substr(0, ofile.find_last_of(".")) + ".exe " + ofile).c_str());
		}
		if(removeFile){
			remove(ofile.c_str());
		}
	}

	return 0;
}
