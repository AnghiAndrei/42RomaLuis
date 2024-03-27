#include <iostream>
using namespace std;

int main(int argc, char **argv){
    if (argc == 1){
        cout<<"* LOUD AND UNBEARABLE FEEDBACK NOISE *"<<"\n";
    }else{
        for(int i=0; argv[i] != NULL; i++)
            cout<<argv[i]<<"\n";
    }
    return 0;
}