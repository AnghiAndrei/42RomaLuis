#include "Harl.hpp"

int main()
{
    Harl harlComp;

    harlComp.complain("DEBUG");
    std::cout << std::endl;
    harlComp.complain("WARNING");
    std::cout << std::endl;
    harlComp.complain("INFO");
    std::cout << std::endl;
    harlComp.complain("ERROR");
    std::cout << std::endl;

    std::cout << "Harl you have to say something: " << std::endl;
    for(int i = 0; i < 5; i++)
    {
        std::string input;
        std::cin >> input;

        harlComp.complain(input);
        std::cout << std::endl;
    }
    return 0;
}
