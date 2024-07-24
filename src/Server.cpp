/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:04:07 by tomoron          #+#    #+#             */
/*   Updated: 2024/07/23 23:07:34 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/*------------------------------- Constructors -------------------------------*/
Server::Server(std::string port, std::string password)
{
	unsigned int port_int;
	std::stringstream port_stream(port);

	_password = password;
	port_stream >> port_int;
	if(port_stream.fail() || !port_stream.eof() || port_stream.bad())
		throw std::exception();
	if(port_int > 65535)
		throw std::exception();
	_servSocketFd = init_socket((uint16_t)port_int);
	if(_servSocketFd == -1)
		throw std::exception();
	this->_clients = std::vector<Client*>();
	this->_pollfds = 0;
}

Server::~Server(void) {}

/*--------------------------------- Methods ----------------------------------*/
int Server::init_socket(uint16_t port)
{
	int					server_fd;
	struct sockaddr_in	s_addr;

	server_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (server_fd < 0)
		perror("socket");
	if (server_fd < 0)
		return (-1);
	s_addr.sin_family = AF_INET;
	s_addr.sin_addr.s_addr = INADDR_ANY;
	s_addr.sin_port = port >> 8 | port << 8;
	if (bind(server_fd, (struct sockaddr *)&s_addr, \
	sizeof(struct sockaddr_in)) < 0)
	{
		close(server_fd);
		perror("bind");
		return (-1);
	}
	if (::listen(server_fd, 50) < 0)
	{
		close(server_fd);
		perror("listen");
		return (-1);
	}
	return (server_fd);
}

void Server::listen()
{
	int a = -1;
	std::cout << "waiting for clients" << std::endl;
	while(true)
	{
		a = accept(_servSocketFd, 0, 0);
		if (a != -1) {
			std::cout << "got client on fd " << a << std::endl;
			this->addClient(a);
		}
		this->receiveData();
		if (this->_clients.size() > 0)
			std::cout << "Ceci est un print de test : " << _clients[0]->getBuffer() << std::endl;
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
	int recv;
	
	recv = poll(this->_pollfds, _clients.size(), 1000);
	if(!recv)
		return ;
	std::cout << "test est ce que ca boucle" << std::endl;
	for(unsigned long i = 0; i < _clients.size(); i++)
	{
		if(this->_pollfds[i].revents & POLLIN)
		{
			_clients[i]->updateBuffer();
		}
		if(this->_pollfds[i].revents & POLLHUP)
		{
			delete _clients[i];
			_clients.erase(_clients.begin() + i);
			std::cout << "removed client " << i << std::endl;
			this->update_pollfds();
		}
	}
}

void	Server::showClient(void)
{
	// for (unsigned int i = 0; i < this->_client.size(); i++)
	// {
	// 	std::cout << "Client " << i << " : " << this->_client.at(i).getUser() << ", " << this->_client.at(i).getNick() << std::endl;
	// }
}

void	Server::addClient(int a) {
	this->_clients.push_back(new Client(a));
	this->update_pollfds();
}

/*--------------------------------- Getters ----------------------------------*/
int	Server::getServSocketFd() {
	return (this->_servSocketFd);
}

std::string	Server::getPassword() {
	return (this->_password);
}

/*--------------------------------- Setters ----------------------------------*/
void		Server::setServSocketFd(int servSocketFd) {
	this->_servSocketFd = servSocketFd;
}

void		Server::setPassword(std::string password) {
	this->_password = password;
}

// void		Server::setClient(Client client)
// {
// 	if (this->_client.size() < 100)
// 		this->_client.push_back(client);
// 	else
// 		throw Server::OutOfRangeClientExeption();
// }

