#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
int main(int argc, char **argv){
    if (argc != 4)
        return (std::cout<<"Marshal: Input Error\n"<<std::endl, 1);
    if (argv[2] == argv[3]){
        return (std::cout<<"Marshal: Input Error\n"<<std::endl, 1);
	}
    std::string text_file="";
    std::string temp="";
    std::ifstream f(argv[1]);
    while(std::getline(f, temp)){
		size_t pos;
		while ((pos = text_file.find(argv[2], pos)) != std::string::npos){
			text_file+=temp.substr(0, pos);
			text_file+=argv[3];
			text_file+=temp.substr(pos+strlen(argv[2]), temp.length());
		}
    }
    f.close();
	char fileout[strlen(argv[1]) + strlen(".replace") + 1];
	strcpy(fileout, argv[1]);
    strcat(fileout, ".replace");
	std::ofstream f2(fileout);
    f2.write(text_file.c_str(), text_file.length());
    f2.close();
    return 0;
}