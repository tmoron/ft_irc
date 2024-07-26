/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:04:07 by tomoron          #+#    #+#             */
/*   Updated: 2024/07/25 22:39:46 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/*------------------------------- Constructors -------------------------------*/
Server::Server(std::string port, std::string password)
{
	unsigned int		port_int;
	std::stringstream	port_stream(port);

	_password = password;
	port_stream >> port_int;
	if(port_stream.fail() || !port_stream.eof() || port_stream.bad())
		throw InvaldPortException();
	if(port_int > 65535)
		throw InvaldPortException();
	_servSocketFd = init_socket((uint16_t)port_int);
	if(_servSocketFd == -1)
		throw InvaldPortException();
	this->_clients = std::vector<Client*>();
	this->_pollfds = 0;
}

Server::~Server(void)
{
	close(_servSocketFd);
	for(unsigned long i = 0; i < _clients.size(); i++)
		delete _clients[i];
	for (unsigned long i = 0; i < _channels.size(); i++)
		delete _channels[i];
	if(this->_pollfds)
		delete[] this->_pollfds;
}

/*--------------------------------- Methods ----------------------------------*/
void	Server::broadcast(std::string message)
{
	for(unsigned int i = 0;i < this->_clients.size(); i++)
	{
		std::cout << "send to " << this->_clients[i]->getFd() << std::endl;
		send(this->_clients[i]->getFd(), message.c_str(), message.length(), MSG_DONTWAIT);
	}
}

int Server::init_socket(uint16_t port)
{
	int					server_fd;
	struct sockaddr_in	s_addr;

	server_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (server_fd < 0)
		throw SocketCreationException();
	s_addr.sin_family = AF_INET;
	s_addr.sin_addr.s_addr = INADDR_ANY;
	s_addr.sin_port = port >> 8 | port << 8;
	if (bind(server_fd, (struct sockaddr *)&s_addr, \
	sizeof(struct sockaddr_in)) < 0)
	{
		close(server_fd);
		throw SocketCreationException();
	}
	if (::listen(server_fd, 50) < 0)
	{
		close(server_fd);
		throw SocketCreationException();
	}
	return (server_fd);
}

void Server::listen()
{
	int a = -1;
	std::cout << "waiting for clients" << std::endl;
	while(!g_sig)
	{
		a = accept(_servSocketFd, 0, 0);
		if (a != -1) {
			std::cout << "got client on fd " << a << std::endl;
			try
			{
				this->addClient(a);
			}
			catch(const ToManyClientsException& e)
			{
				std::cerr << e.what() << '\n';
			}

		}
		this->receiveData();
	}
}

void Server::update_pollfds()
{
	if(this->_pollfds)
		delete[] _pollfds;
	this->_pollfds = new struct pollfd[_clients.size()];
	for(unsigned long i = 0; i < _clients.size(); i++)
	{
		this->_pollfds[i].fd = _clients[i]->getFd();
		this->_pollfds[i].events = POLLIN;
	}
}

void	Server::receiveData(void)
{
	int	recv;

	recv = poll(this->_pollfds, _clients.size(), 1000);
	if(!recv)
		return ;
	for(unsigned long i = 0; i < _clients.size(); i++)
	{
		if(this->_pollfds[i].revents & POLLIN)
		{
			if (_clients[i]->updateBuffer())
			{
				delete _clients[i];
				_clients.erase(_clients.begin() + i);
				std::cout << "removed client " << i << std::endl;
				this->update_pollfds();
			}
		}
	}
}

void	Server::addClient(int a) {
	this->_clients.push_back(new Client(a, *this));
	this->update_pollfds();
}

/*--------------------------------- Channel ----------------------------------*/
Channel	*Server::getChannel(std::string &name, Client *client, int create)
{
	unsigned int	i;
	Channel *res;

	for (i = 0; i < this->_channels.size(); i++)
	{
		if (this->_channels[i]->getName() == name)
		{
			return (this->_channels[i]);
		}
	}
	if(!create)
		return(0);
	if(name[0] != '#')
		return(0);
	res = new Channel(name, client);
	this->_channels.push_back(res);
	return(res);
}

std::vector<Channel*>	&Server::getChannels()
{
	return (this->_channels);
}

void	Server::delChannel(std::string name)
{
	unsigned int	i;
	for (i = 0; i < this->_channels.size() - 1; i++)
	{
		if (this->_channels[i]->getName() == name)
		{
			this->_channels.erase(this->_channels.begin() + i);
			return ;
		}
	}
}

void	Server::exec(const std::string &full_cmd, Client &client)
{
	std::string	command;
	std::string	args;

	if(full_cmd.find(' ', 0) != std::string::npos)
	{
		command = full_cmd.substr(0, full_cmd.find(' ' , 0));
		args = full_cmd.substr(full_cmd.find(' ', 0) + 1);
		args = trim(' ', args);
	}
	else
	{
		command = full_cmd;
		args = "";
	}
	this->_commandManager.execCommand(command, args, client, *this);
}

Server	&Server::addCommand(std::string cmdName, void (*funct)(const std::string &, Client &, Server &))
{
	this->_commandManager.addCommand(cmdName, funct);
	return(*this);
}


/*--------------------------------- Getters ----------------------------------*/
int	Server::getServSocketFd() {
	return (this->_servSocketFd);
}

std::string	Server::getPassword() {
	return (this->_password);
}

std::vector<Client*>	&Server::getClients()
{
	return (this->_clients);
}

Client	*Server::getClient(std::string nick)
{
	for(unsigned long i = 0; i < _clients.size(); i++)
	{
		if(_clients[i]->getNick() == nick)
			return(_clients[i]);
	}
	return NULL;
}
/*--------------------------------- Setters ----------------------------------*/
void	Server::setServSocketFd(int servSocketFd) {
	this->_servSocketFd = servSocketFd;
}

void	Server::setPassword(std::string password) {
	this->_password = password;
}
