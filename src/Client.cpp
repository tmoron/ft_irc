/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:05:52 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/24 15:32:56 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

/*------------------------------- Constructors -------------------------------*/
Client::Client(int fd) {
	_fd = fd;
	_user = "";
	_nick = "";
	_buffer = "";
	_loggedIn = false;
}

Client::~Client()
{
	close(_fd);
}

/*--------------------------------- Methods ----------------------------------*/
int	Client::updateBuffer()
{
	char buffer[1024];
	unsigned long len;

	std::cout << "new data form client " << this->_fd << std::endl;
	len = recv(this->_fd, buffer, 1024, MSG_DONTWAIT);
	if(!len)
		return (1);
	std::cout << "add" << std::endl;
	this->_buffer += std::string(buffer, len);
	this->handleBuffer();
	return(0);
}

void Client::handleBuffer()
{
	//unsigned long len;

	std::cout << "Buffer for client on fd " << this->_fd << " :" << std::endl;
	std::cout << this->_buffer << std::flush;
	//while(_buffer.find('\n', 0) != std::string::npos) //WIP do whatever you want
	//{
	//	len = _buffer.find('\n', 0) + 1;
	//	_buffer.
	//}
}

/*--------------------------------- Setters ----------------------------------*/
void		Client::setUser(std::string user)
{
	this->_user = user;
}
void		Client::setNick(std::string nick)
{
	this->_nick = nick;
}
void	Client::setLoggedIn(bool b)
{
	this->_loggedIn = b;
}

/*--------------------------------- Getters ----------------------------------*/
std::string	Client::getUser()
{
	return (this->_user);
}
std::string	Client::getNick()
{
	return (this->_nick);
}

int Client::getFd()
{
	return(this->_fd);
}

std::string Client::getBuffer()
{
	return (this->_buffer);
}

bool	Client::getLoggedIn()
{
	return (this->_loggedIn);
}

std::vector<Client*>	&Server::getClients()
{
	return (this->_clients);
}
