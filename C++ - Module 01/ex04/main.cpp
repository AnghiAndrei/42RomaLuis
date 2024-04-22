#include <string>
#include <iostream>
#include <fstream>
int main(int argc, char **argv){
    if (argc != 4)
        return (cout<<"Marshal: Input Error\n", 1);
    if (argv[2] == argv[3])
        return (cout<<"Marshal: Input Error\n", 1);
    std::string text_file=NULL;
    std::string temp=NULL;
    fstream file;
    f.open(argv[1], ios::in);
    while(!file.eof()){
        getline(f, temp);
        text_file+=temp;
    }
    f.close();
    temp=NULL;
    while (1){
        size_t found=text_file.find(argv[3]);
        if (found == string::npos)
            break;
        size_t pos=0;
        for(size_t i=pos; i != found; i++;){
            temp+=text_file[i];
            pos++;
        }
        temp+=argv[3];
        pos+=std::strlen(argv[2]);
        for(size_t i=pos; text_file[i] != '\0'; i++;){
            temp+=text_file[i];
        }
    }
    f.open(argv[1]+".replace", ios::out);
    file<<temp;
    f.close();
    return 0;
}