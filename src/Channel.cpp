/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:42:37 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/24 15:29:25 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

/*------------------------------- Constructors -------------------------------*/
Channel::Channel(/* args */)
{
}

Channel::Channel(std::string name, std::string topic, std::string password) : _name(name), _topic(topic), _password(password)
{
}

Channel::~Channel()
{
}

/*--------------------------------- Methods ----------------------------------*/
void	Channel::addClient(Client* client)
{
	if (_clients.size() > 100)
		return ;
	// throw std::exception();
	this->_clients.push_back(client);
}

/*--------------------------------- Getters ----------------------------------*/
std::string Channel::getName(void)
{
	return this->_name;
}

std::string Channel::getTopic(void)
{
	return this->_topic;
}

std::string Channel::getPassword(void)
{
	return this->_password;
}

std::vector<Client*> &Channel::getClients(void)
{
	return this->_clients;
}

/*--------------------------------- Setters ----------------------------------*/
void	Channel::setName(std::string name)
{
	this->_name = name;
}

void	Channel::setTopic(std::string topic)
{
	this->_topic = topic;
}

void	Channel::setPassword(std::string password)
{
	this->_password = password;
}
