#include "loser.hpp"

int replaceFile(char **argv, std::string& originalStr)
{
    std::string s1 = argv[2];
    std::string s2 = argv[3];

    size_t pos = originalStr.find(s1);
    while(pos != std::string::npos)
    {
        originalStr.replace(pos, s1.length(), s2);
        pos = originalStr.find(s1, pos + s2.length());
    }
    
    std::ofstream outputFile(argv[1]);
    if(!outputFile.is_open()){
        std::cout << "Error opening output file." << std::endl;
        return 1;
    }

    outputFile << originalStr;
    outputFile.close();
    return 0;
}

int main(int argc, char **argv)
{
    char c;
    std::string str;
    std::fstream file;
    if(argc != 4)
    {
        std::cout << "usage: replace <file> old_word new_word" << std::endl;
        return 1;
    }
    file.open(argv[1]);
    if(file.fail()){
        std::cout << "Error: " << argv[1] << ": no such file or directory"<< std::endl;
        return 1;
    }
    while(!file.eof() && file >> std::noskipws >> c){
        str += c;
    }
    file.close();
    return replaceFile(argv, str);
}


