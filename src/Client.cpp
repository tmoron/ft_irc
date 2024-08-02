/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:05:52 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/02 15:38:56 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

/*------------------------------- Constructors -------------------------------*/
Client::Client(int fd, Server &srv): _server(srv)
{
	_fd = fd;
	_nick = "";
	_buffer = "";
	_loggedIn = false;

	_user = "";
	_hostname = "";
	_servername = "";
	_realname = "";
	_quit = 0;
}

Client::~Client()
{
	std::cout << "delete client : " << _fd << std::endl;
	close(_fd);
}

/*--------------------------------- Methods ----------------------------------*/
void	Client::quit()
{
	this->_quit = 1;
}

int	Client::updateBuffer()
{
	char			buffer[1024];
	unsigned long	len;

	len = recv(this->_fd, buffer, 1024, MSG_DONTWAIT);
	if(!len || len == (unsigned long)-1)
		return (1);
	this->_buffer += std::string(buffer, len);
	this->handleBuffer();
	if(this->_quit)
		return(1);
	return(0);
}

void	Client::handleBuffer()
{
	unsigned long	len;

	while(_buffer.find('\n', 0) != std::string::npos) 
	{
		len = _buffer.find('\n', 0);
		_server.exec(_buffer.substr(0, len), *this);
		_buffer.erase(0, len + 1);
	}
}

void	Client::sendStr(std::string msg)
{
	msg += "\r\n";
	send(this->_fd, msg.c_str(), msg.length(), MSG_DONTWAIT);
}

int		Client::sendMsg(Client &from ,const std::string &to,const std::string &message)
{
	if(!this->isRegistered())
		return(0);
	std::stringstream msg;
	msg << ":" << from.getIdentifier() << " PRIVMSG ";
	msg << to << " " << message;
	this->sendStr(msg.str());
	return(1);
}

void	Client::sendInfo(Channel *channel, int code, std::string data)
{
	std::stringstream	ss;

	ss << ":localhost " << code;
	ss << " " << this->_nick;
	if(channel)
		ss << " " << channel->getName();
	ss << " " << data;
	this->sendStr(ss.str());
}

int	Client::isRegistered()
{
	return(this->_loggedIn && this->_user.length() && this->_nick.length());
}

std::string	Client::getIdentifier()
{
	return(this->_nick + "!" + this->_user + "@localhost");
}
			
std::string Client::getWho(Channel *channel)
{
	std::string res;

	res = channel->getName() + " " + this->_user + " ";
	res += this->_hostname + " " +  this->_servername + " ";
	res += this->_nick + " H" + (channel->isOperator(this) ? "@" : "");
	res += " :0 " + this->_realname;
	return(res);
}

/*--------------------------------- Setters ----------------------------------*/
void	Client::setUser(std::string user)
{
	this->_user = user;
}
void	Client::setNick(std::string nick)
{
	if(!this->_nick.length())
		this->sendStr(":localhost 001 " + nick + " :welcome to the best irc server you've ever seen");
	else
		this->_server.sendStr(":" + this->_nick+" NICK " + nick);
	this->_nick = nick;
}
void	Client::setLoggedIn(bool b)
{
	this->_loggedIn = b;
}
void	Client::setHostname(std::string hostname)
{
	this->_hostname = hostname;
}
void	Client::setServername(std::string servername)
{
	this->_servername = servername;
}
void	Client::setRealname(std::string realname)
{
	this->_realname = realname;
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

std::string	Client::getHostname()
{
	return(this->_hostname);
}

std::string Client::getServername()
{
	return(this->_servername);
}

std::string Client::getRealname()
{
	return(this->_realname);
}
