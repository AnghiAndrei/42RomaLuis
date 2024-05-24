/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:10:29 by lde-mich          #+#    #+#             */
/*   Updated: 2024/04/29 17:55:10 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>

#define TIMEOUT 5

class Cgi
{
	private:


	public:

		std::string getFileExtension(const std::string& fileName);
		int exeScript(std::string path);
		
		Cgi();
		~Cgi();


		class ExecuteFileException: public std::exception
        {
            public:
                virtual const char	*what() const throw()
				{
					return ("Error → exec failed");
				};
        };

		class ForkException: public std::exception
        {
            public:
                virtual const char	*what() const throw()
				{
					return ("Errore → processo figlio non creato");
				};
        };

		class PermissionFileException: public std::exception
        {
            public:
                virtual const char	*what() const throw()
				{
					return ("Errore → modifica dei permessi fallita");
				};
        };

		class OpenFileException: public std::exception
        {
            public:
                virtual const char	*what() const throw()
				{
					return ("Errore → apertura file fallita");
				};
        };

		class DupException: public std::exception
        {
            public:
                virtual const char	*what() const throw()
				{
					return ("Errore → Duplicazione file descriptor fallita");
				};
        };
	
};
