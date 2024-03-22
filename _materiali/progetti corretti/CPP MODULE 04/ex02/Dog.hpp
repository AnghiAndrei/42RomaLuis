/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcardina <fcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 01:20:26 by fcardina          #+#    #+#             */
/*   Updated: 2024/02/03 19:35:02 by fcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

# include "AAnimal.hpp"
# include "Brain.hpp"

class Dog : public AAnimal //Derived class
{
	private:
		Brain* brain;
		std::string type;
		
	public:
		Dog(void);
		Dog(const Dog &original);
		Dog &operator=(const Dog &to_copy);
		~Dog(void);

		void makeSound(void) const; //Polymorphic behavior
		void getIdea(void)const;
		Brain* getBrain(void) const;
};

#endif
