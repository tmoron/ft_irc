/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:05:52 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/26 14:44:11 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

/*------------------------------- Constructors -------------------------------*/
Client::Client(int fd, Server &srv): _server(srv)
{
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
	char			buffer[1024];
	unsigned long	len;

	std::cout << "new data form client " << this->_fd << std::endl;
	len = recv(this->_fd, buffer, 1024, MSG_DONTWAIT);
	if(!len || len == (unsigned long)-1)
		return (1);
	std::cout << "add" << std::endl;
	std::cout << "len : " << len << std::endl;
	this->_buffer += std::string(buffer, len);
	this->handleBuffer();
	return(0);
}

void	Client::handleBuffer()
{
	unsigned long	len;
	std::string		command;

	std::cout << "Buffer for client on fd " << this->_fd << " :" << std::endl;
	std::cout << this->_buffer << std::flush;
	while(_buffer.find('\n', 0) != std::string::npos) 
	{
		len = _buffer.find('\n', 0);
		_server.exec(_buffer.substr(0, len), *this);
		_buffer.erase(0, len + 1);
	}
}

void	Client::sendStr(std::string msg)
{
	msg += "\n";
	send(this->_fd, msg.c_str(), msg.length(), MSG_DONTWAIT);
}

int		Client::sendMessage(Client &from ,const std::string &to,const std::string &message)
{
	if(!this->isRegistered())
		return(0);
	std::stringstream msg;
	msg << ":" << from.getIdentifier() << " ";
	msg << to << " :" << message;
	this->sendStr(msg.str());
	return(1);
}

void	Client::sendInfo(Channel *channel, int code, std::string description)
{
	std::stringstream	ss;

	ss << ":localhost " << code;
	if(channel)
		ss << " " << channel->getName();
	ss << " :" << description;
	this->sendStr(ss.str());
}

int	Client::isRegistered()
{
	return(this->_loggedIn && this->_user.length() && this->_nick.length());
}

void	Client::joinChannel(const std::string name)
{
	std::string msg;

	msg = ":" + this->getIdentifier() + " JOIN " + name;
	this->sendStr(msg);
}

std::string	Client::getIdentifier()
{
	return(this->_nick + "!" + this->_user + "@localhost");
}

/*--------------------------------- Setters ----------------------------------*/
void	Client::setUser(std::string user)
{
	this->_user = user;
}
void	Client::setNick(std::string nick)
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

int	Client::getFd()
{
	return(this->_fd);
}

std::string	Client::getBuffer()
{
	return (this->_buffer);
}

int Client::getLoggedIn()
{
	return(this->_loggedIn);
}

