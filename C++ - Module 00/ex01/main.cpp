#include <iostream>
#include <string>
using namespace std;

int main(){
    string  str;
    PhoneBook pb;
    while(1){
        cout<<"PhoneBook>";
        cin>>str;
        if (str=="EXIT")
            exit(0);
        else if (str=="SEARCH")
            pb.search();
        else if (str=="ADD"){
            Contact new_c=;

        }else
            cout<<"WTF?\n";
    }
    return 0;
}
