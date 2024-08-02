/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:04:07 by tomoron          #+#    #+#             */
/*   Updated: 2024/08/02 23:10:44 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include "OpenaiReq.hpp"
#include "prompts.hpp"

/*------------------------------- Constructors -------------------------------*/

Bot::Bot(std::string ip, std::string port)
{
	unsigned int		port_int;
	std::stringstream	port_stream(port);

	genName();
	port_stream >> port_int;
	if(port_stream.fail() || !port_stream.eof() || port_stream.bad())
		throw InvaldPortException();
	if(port_int > 65535)
		throw InvaldPortException();
	_connFd = init_connection(ip.c_str(), (uint16_t)port_int);
	if(_connFd == -1)
		throw InvaldPortException();
	this->_pollfd.fd = _connFd;
	this->_pollfd.events = POLLIN;
	this->_pollfd.revents = 0;
	this->_stop = 0;
}

Bot::~Bot(void)
{
	if(this->_connFd > 2)
		close(this->_connFd);
	for (std::map<std::string, GPTHistory *>::iterator it = _histories.begin(); it != _histories.end(); it++)
		delete it->second;
}

/*--------------------------------- Methods ----------------------------------*/
void Bot::genName()
{
	this->_name = " ";
	while(this->_name.find(' ', 0) != std::string::npos)
	{
		OpenaiReq nameReq("[{\"role\":\"user\",\"content\":\"" NAME_PROMPT "\"}]");
		this->_name = nameReq.send();
		std::cout << "generated name : " << this->_name << std::endl;
	}
}

int Bot::init_connection(const char *ip, uint16_t port)
{
    int                 sock_fd;
    struct sockaddr_in  serv_addr;

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
		throw SocketCreationException();
    ft_bzero(&serv_addr, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = port >> 8 | port << 8;
    if(connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in)))
		throw ConnexionException();
    return (sock_fd);
}

void Bot::send(std::string str)
{
	::send(this->_connFd, str.c_str(), str.length(),MSG_DONTWAIT); 
}

void	Bot::exec(std::string buffer)
{
	buffer = removeChar(buffer, '\r');
	std::vector<std::string> argSplit = ft_split_irc(buffer);
	std::string response;

	for(unsigned int i = 0; i < argSplit.size(); i++)
		std::cout << i << " : " << argSplit[i] << std::endl;
	if (argSplit.size() < 2)
		return;
	if (argSplit[1] == "433")
	{
		genName();
		send("NICK " + this->_name + "\r\n");
		return;
	}
	if (argSplit[1] == "464")
	{
		throw WrongPasswordException();
	}
	if (buffer.find("PRIVMSG") != std::string::npos && argSplit.size() >= 4)
	{
		std::string name = argSplit[0].substr(0, argSplit[0].find('!'));
		if(name == this->_name)
			return ;
		addHistory(argSplit[0], argSplit[3], "user");
		OpenaiReq req(_histories[argSplit[0]]->getHistoryJson());
		response = req.send(); 
		send("PRIVMSG " + name + " :" + response + "\r\n");
		addHistory(argSplit[0], response, "assistant");
	}
}

void	Bot::handleBuffer()
{
	unsigned long	len;
	while(_buffer.find('\n', 0) != std::string::npos) 
	{
		len = _buffer.find('\n', 0);
		exec(_buffer.substr(0, len));
		_buffer.erase(0, len + 1);
	}
}

void Bot::listen()
{
	char tmp[1024];
	unsigned long len;

	while(!g_sig && !this->_stop)
	{
		if(poll(&this->_pollfd, 1, 200))
		{
			len = recv(this->_connFd, tmp, 1024, MSG_DONTWAIT);
			if(len == (unsigned long)-1)
				return;		
			if(len)
				this->_buffer += std::string(tmp, len);
			Bot::handleBuffer();
		}
	}
		
}

void Bot::login(std::string pass)
{
	send("PASS " + pass + "\r\n");
	send("NICK " + _name + "\r\n");
	send("USER " + _name + " 0 * :" + _name + "\r\n");
}

void	Bot::addHistory(std::string name, std::string msg,const std::string role)
{
	if(_histories.find(name) == _histories.end())
		_histories[name] = new GPTHistory(name);
	_histories[name]->addHistory(role, msg);
}
