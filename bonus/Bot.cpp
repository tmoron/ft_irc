/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:04:07 by tomoron          #+#    #+#             */
/*   Updated: 2024/07/31 17:57:13 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

/*------------------------------- Constructors -------------------------------*/

Bot::Bot(std::string ip, std::string port)
{
	unsigned int		port_int;
	std::stringstream	port_stream(port);

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
}

/*--------------------------------- Methods ----------------------------------*/
int Bot::init_connection(const char *ip, uint16_t port)
{
    int                 sock_fd;
    struct sockaddr_in  serv_addr;

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
	{
		std::cout << "A" << std::endl;
		throw std::exception();
	}
    ft_bzero(&serv_addr, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = port >> 8 | port << 8;
    if(connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in)))
		throw std::exception();
    return (sock_fd);
}

void Bot::send(std::string str)
{
	::send(this->_connFd, str.c_str(), str.length(),MSG_DONTWAIT); 
}

void	Bot::exec(unsigned long len)
{
	std::vector<std::string> argSplit = ft_split_irc(_buffer);

	std::cout << "exec : " << _buffer << std::endl;
	if (_buffer.find("PRIVMSG") != std::string::npos)
	{
		if (argSplit.size() < 4)
			return;
		addHistory(argSplit[0], argSplit[3]);
	}
}

void	Bot::handleBuffer()
{
	unsigned long	len;

	while(_buffer.find('\n', 0) != std::string::npos) 
	{
		len = _buffer.find('\n', 0);
		exec(len);
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
			std::cout << _buffer << std::endl;
			Bot::handleBuffer();
			std::cout << "buffer : " << _buffer << std::endl;
		}
	}
		
}

void Bot::login(std::string pass)
{
	this->send("PASS " + pass + "\r\n");
	this->send("NICK bot\r\n");
	this->send("USER bot 0 * :bot\r\n");
}

void	Bot::addHistory(std::string name, std::string msg)
{
	if(_histories.find(name) == _histories.end())
		_histories[name] = new GPTHistory(name);
	_histories[name]->addHistory("user", msg);
}