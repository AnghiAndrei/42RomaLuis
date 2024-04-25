#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP
#include <iostream>
#include <string>
class WrongAnimal{
    protected:
        std::string type;
    public:
        WrongAnimal &operator=(WrongAnimal &ncopy);
		virtual void makeSound() const;
        std::string getType() const;
        WrongAnimal(const WrongAnimal &ncopy);
        WrongAnimal(std::string type2);
        virtual ~WrongAnimal();
        WrongAnimal();
};
#endif