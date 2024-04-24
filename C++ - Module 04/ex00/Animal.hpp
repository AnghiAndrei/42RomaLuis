#ifndef ANIMAL_HPP
#define ANIMAL_HPP
class Animal{
    protected:
        std::string type;
    public:
        Animal(std::string type2);
        Animal &operator=(Animal &copy);
        std::string get_Type();
        ~Animal();
};
#endif