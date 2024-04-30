#ifndef BRAIN_HPP
#define BRAIN_HPP
#include <string>
#include <iostream>
class Brain{
	protected:
		std::string ideas[100];
	public:
		Brain &operator=(Brain &ncopy);
		Brain(const Brain &ncopy);
		~Brain();
		Brain();
};
#endif