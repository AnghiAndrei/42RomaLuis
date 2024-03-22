/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcardina <fcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:11:39 by fcardina          #+#    #+#             */
/*   Updated: 2024/02/06 03:30:08 by fcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <iostream>
# include <string>
# include "Brain.hpp"

class Animal  //Base class
{
	protected:
		std::string type;
		Brain* brain;
		
	public:
		Animal(void);
		Animal(const Animal &to_copy);
		Animal &operator=(const Animal &to_copy);
		virtual ~Animal(void); 

		virtual std::string getType(void) const;
		virtual void setType(std::string type);
		virtual Brain* getBrain(void) const;

		virtual void makeSound(void) const;
};

#endif
