/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:42:04 by lde-mich          #+#    #+#             */
/*   Updated: 2024/02/27 17:55:07 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

int main ()
{
	Base *obj;

	srand(time(NULL));
	obj = generate();
	identify(obj);
	identify(*obj);

	return (0);
}





