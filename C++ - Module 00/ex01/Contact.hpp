class Contact{
    public:
        std::string name;
        std::string name2;
        std::string surname;
        std::string dse;
        std::string tel;

        ~Contact();
        Contact(){
            std::cout<<"First name: ";
            std::cin>>name;
            std::cout<<"Last name: ";
            std::cin>>name2;
            std::cout<<"Surname: ";
            std::cin>>surname;
            std::cout<<"Phone: ";
            std::cin>>tel;
            std::cout<<"Darkest secret: ";
            std::cin>>dse;
        }
};