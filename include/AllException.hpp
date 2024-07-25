/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AllException.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:28:01 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/25 15:08:25 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLEXCEPTION_HPP
# define ALLEXCEPTION_HPP

# include <exception>
# include <string>

class InvaldPortException : public std::exception
{
    public:
        virtual const char* what() const throw()
        {
            return "\e[2m\033[31mInvalid Port. \e[0m";
        }
};

class OutOfRangeClientExeption : public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return "\e[2m\033[31mOut of range client. \e[0m";
		}

};

class ToManyClientsException : public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return "\e[2m\033[31mTo many clients. \e[0m";
	}
};

class SocketCreationException : public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return "\e[2m\033[31mSocket creation failed. \e[0m";
	}
};

#endif