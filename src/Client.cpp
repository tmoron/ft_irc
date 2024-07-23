/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:05:52 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/23 11:34:44 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

/*------------------------------- Constructors -------------------------------*/
Client::Client() : _nb(0), _user("default"), _buffer("")
{
}

Client::Client(std::string user, std::string nick) : _nb(0), _buffer("")
{
	// verifer ou non le format username et nickname 
	this->_user = user;
	this->_nick = nick;
}

Client::~Client()
{
}

/*--------------------------------- Methods ----------------------------------*/

/*--------------------------------- Setters ----------------------------------*/
void	Client::setBuffer(std::string buffer)
{
	this->_buffer = buffer;
}

void		Client::setUser(std::string user)
{
	this->_user = user;
}
void		Client::setNick(std::string nick)
{
	this->_nick = nick;
}

/*--------------------------------- Getters ----------------------------------*/
std::string	Client::getBuffer()
{
	return (this->_buffer);
}
std::string	Client::getUser()
{
	return (this->_user);
}
std::string	Client::getNick()
{
	return (this->_nick);
}
