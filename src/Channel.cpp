/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:42:37 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/25 19:25:09 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

/*------------------------------- Constructors -------------------------------*/
Channel::Channel(void)
{
}

Channel::Channel(std::string name, Client *client) : _name(name), _operator(client)
{
}

Channel::~Channel(void)
{
}

/*--------------------------------- Methods ----------------------------------*/
void	Channel::addClient(Client* client)
{
	if (_clients.size() > 100)
		return ;
	else
		throw ToManyClientsException();
	this->_clients.push_back(client);
}

void	Channel::delClient(std::string nick)
{
	for (unsigned int i = 0; i < this->_clients.size() - 1; i++)
	{
		if (this->_clients[i]->getNick() == nick)
			this->_clients.erase(this->_clients.begin() + i);
	}
}

int	Channel::inviteInChannel(Client &invitor,	Client &invited,  Channel &channel)
{
	if (invitor.getNick() != channel.getOperator()->getNick())
	{
		writeError(invitor, 0, 482, ":You're not channel operator");
	}
	channel.getInvite().push_back(&invited);
	return (0);
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

Client *Channel::getOperator()
{
	return this->_operator;
}

std::vector<Client*> &Channel::getInvite(void)
{
	return this->_invite;
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

void Channel::setOperator(Client *newoperator)
{
	this->_operator = newoperator;
}
