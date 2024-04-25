#ifndef WRONGCAT_HPP
#define WRONGCAT_HPP
#include <iostream>
#include <string>
#include "WrongAnimal.hpp"
class WrongAnimal;
class WrongCat : public WrongAnimal{
    protected:
        std::string type;
    public:
        WrongCat &operator=(WrongCat &ncopy);
        std::string getType() const;
        WrongCat(const WrongCat &ncopy);
        WrongCat(std::string type2);
        virtual ~WrongCat();
        WrongCat();
};
#endif