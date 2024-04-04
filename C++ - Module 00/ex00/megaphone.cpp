#include <iostream>

int main(int argc, char **argv){
    if (argc == 1){
        std::cout<<"* LOUD AND UNBEARABLE FEEDBACK NOISE *"<<"\n";
    }else{
        for(int i=0; argv[i] != NULL; i++)
            for(int i=0; argv[i] != '\0'; i++){
                av[i][j] = std::toupper(av[i][j]);
                std::cout<<argv[i][j];
            }
        std::cout << std::endl;
    }
    return 0;
}