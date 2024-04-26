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
	if (!f.is_open())
        return (std::cout<<"Marshal: "<<argv[1]<<" error file"<<std::endl, 1);
	char fileout[strlen(argv[1]) + strlen(".replace") + 1];
	strcpy(fileout, argv[1]);
    strcat(fileout, ".replace");
	std::ofstream f2(fileout);
	if (!f2.is_open())
        return (std::cout<<"Marshal: "<<fileout<<" error file"<<std::endl, 1);
    while(std::getline(f, temp)){
		size_t pos=0;
		while ((pos = temp.find(argv[2], pos)) != std::string::npos){
			text_file+=temp.substr(0, pos);
			text_file+=argv[3];
		    temp.erase(0, pos+strlen(argv[2]));
		}
        text_file+=temp;
		if (!f.eof())text_file+='\n';
    }
    f.close();
    f2.write(text_file.c_str(), text_file.length());
    f2.close();
    return 0;
}