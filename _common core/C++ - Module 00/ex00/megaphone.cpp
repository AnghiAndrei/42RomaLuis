#include <iostream>

int main(int argc, char **argv){
    if (argc == 1){
        std::cout<<"* LOUD AND UNBEARABLE FEEDBACK NOISE *"<<"\n";
    }else{
        for(int i=1; argv[i] != NULL; i++)
            for(int j=0; argv[i][j] != '\0'; j++){
                argv[i][j] = std::toupper(argv[i][j]);
                std::cout<<argv[i][j];
            }
        std::cout << std::endl;
    }
    return 0;
}