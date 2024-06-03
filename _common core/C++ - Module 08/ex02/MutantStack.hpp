#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP
#include <iterator>
#include <iostream>
#include <stack>
#include <deque>
template <typename T, typename Container = std::deque<T> >
class MutantStack : public std::stack<T, Container> {
	public:
		typedef typename Container::iterator iterator;
		typedef typename Container::const_iterator const_iterator;
		typedef typename Container::reverse_iterator reverse_iterator;
		typedef typename Container::const_reverse_iterator const_reverse_iterator;

		MutantStack(const MutantStack &ncopy) : std::stack<T, Container>(ncopy){}
		const_reverse_iterator rbegin() const{return this->c.rbegin();}
		const_reverse_iterator rend() const{return this->c.rend();}
		const_iterator begin() const{return this->c.begin();}
		reverse_iterator rbegin(){return this->c.rbegin();}
		const_iterator end() const{return this->c.end();}
		reverse_iterator rend(){return this->c.rend();}
		MutantStack() : std::stack<T, Container>(){}
		iterator begin(){return this->c.begin();}
		iterator end(){return this->c.end();}
		~MutantStack(){}
		MutantStack &operator=(const MutantStack &ncopy){
			std::stack<T, Container>::operator=(ncopy);
			return *this;
		}
};
#endif