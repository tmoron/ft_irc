/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:42:37 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/30 17:28:30 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

/*------------------------------- Constructors -------------------------------*/
Channel::Channel(void)
{
}

Channel::Channel(std::string name) : _name(name)
{
	this->init();
}

Channel::~Channel(void)
{
}

/*--------------------------------- Methods ----------------------------------*/
void Channel::init()
{
	this->_operators.empty();
	this->_clients.empty();
	this->_invite.empty();
	this->_topic = "";
	this->_password = "";
	this->_userLimit = MAX_CHANNEL_USER;
	this->_inviteOnly = false;
	this->_topicOperatorOnly = false;
}

std::string	Channel::getMode()
{
	std::stringstream res;

	if (_inviteOnly)
		res << "i";
	if (_topicOperatorOnly)
		res << "t";
	if (_password.length())
		res << "k";
	if (_userLimit)
		res << "l " << _userLimit;

	return (res.str());
}

int	Channel::addClient(Client* client, const std::string &pass)
{
	if(!this->_clients.size())
	{
		this->init();
		this->_operators.push_back(client);
	}
	if(!client)
		return(0);
	if (_clients.size() >= this->_userLimit)
	{
		client->sendInfo(this, 471, ":Cannot join channel (+l)");
		return(0);
	}
	if(this->_inviteOnly && !this->isInvited(client))
	{
		client->sendInfo(this, 473, ":Cannot join channel (+i)");
		return(0);
	}
	if(this->_password.length() && pass != this->_password)
	{
		client->sendInfo(this, 475, ":Cannot join channel (+k)");
		return(0);
	}
	this->delInvite(client);
	if(std::find(this->_clients.begin(), this->_clients.end(), client) == this->_clients.end())
		this->_clients.push_back(client);
	return(1);
}

void	Channel::delClient(Client *client,const std::string &reason)
{
	if(!client)
		return;
	for (unsigned int i = 0; i < this->_clients.size(); i++)
	{
		if (this->_clients[i] == client)
		{
			if(reason.length())
				this->sendStr(":" + client->getNick() + " PART " + this->_name + " " + reason);
			else
				this->sendStr(":" + client->getNick() + " PART " + this->_name);
			this->delOperator(this->_clients[i]);
			this->_clients.erase(this->_clients.begin() + i);
			return;
		}
	}
}

void	Channel::delClient(std::string &nick,const std::string &reason)
{
	for (unsigned int i = 0; i < this->_clients.size(); i++)
	{
		if (this->_clients[i]->getNick() == nick)
		{
			if(reason.length())
				this->sendStr(":" + nick + " PART " + this->_name + " " + reason);
			else
				this->sendStr(":" + nick + " PART " + this->_name);
			this->delOperator(this->_clients[i]);
			this->_clients.erase(this->_clients.begin() + i);
			return;
		}
	}
}

void	Channel::delClient(std::string &nick)
{
	for (unsigned int i = 0; i < this->_clients.size(); i++)
	{
		if (this->_clients[i]->getNick() == nick)
		{
			this->delOperator(this->_clients[i]);
			this->_clients.erase(this->_clients.begin() + i);
			return;
		}
	}
}

void Channel::delOperator(Client *client)
{
	std::vector<Client *>::iterator pos;

	pos = std::find(this->_operators.begin(), this->_operators.end(), client);
	if(pos == this->_operators.end())
		return ;
	this->_operators.erase(pos);
}

int	Channel::inviteInChannel(Client &invitor, Client &invited, Channel &channel)
{
	if (!isOperator(&invitor))
	{
		invitor.sendInfo(0, 482, ":You're not channel operator");
	}
	invited.sendStr(":" + invitor.getNick() + " INVITE " + invited.getNick() + " " + channel.getName());
	channel.getInvite().push_back(&invited);
	return (0);
}

void	Channel::delInvite(Client *client)
{
	std::vector<Client *>::iterator pos;

	pos = std::find(this->_invite.begin(), this->_invite.end(), client);
	if(pos == this->_invite.end())
		return;
	this->_invite.erase(pos);
}

bool Channel::isInvited(Client *client)
{
	return(std::find(this->_invite.begin(), this->_invite.end(), client) != this->_invite.end());
}

bool Channel::isOperator(Client *client)
{
	return(std::find(this->_operators.begin(), this->_operators.end(), client) != this->_operators.end());
}

bool Channel::isOnChannel(Client *client)
{
	return(std::find(this->_clients.begin(), this->_clients.end(), client) != this->_clients.end());
}

std::string Channel::getNames()
{
	std::string res;

	res = "";
	for(unsigned int i = 0; i < this->_clients.size(); i++)
	{
		if(std::find(this->_operators.begin(), this->_operators.end(), this->_clients[i]) != this->_operators.end())
			res += "@";
		res += this->_clients[i]->getNick();
		if(i != this->_clients.size() - 1)
			res += " ";
	}
	return(res);
}

void Channel::sendStr(std::string str)
{
	for(unsigned long i = 0; i < _clients.size(); i++)
		_clients[i]->sendStr(str);
}

void		Channel::sendMsg(Client &client, const std::string &message)
{
	for(unsigned long i = 0; i < _clients.size(); i++)
		if(&client != _clients[i])
			_clients[i]->sendMsg(client, this->_name, message);
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

std::vector<Client*> Channel::getOperators()
{
	return this->_operators;
}

std::vector<Client*> &Channel::getInvite(void)
{
	return this->_invite;
}

bool Channel::getInviteOnly(void)
{
	return (this->_inviteOnly);
}

long unsigned int Channel::getUserLimit(void)
{
	return (this->_userLimit);
}

bool Channel::getTopicOperatorOnly(void)
{
	return (this->_topicOperatorOnly);
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

void Channel::addOperator(Client *newoperator)
{
	this->_operators.push_back(newoperator);
}

void Channel::setInviteOnly(bool boolean, Client *client)
{
	std::stringstream msg;

	msg << ":" << client->getNick() << " MODE " << this->_name << " ";
	msg << (boolean ? "+i" : "-i");
	this->sendStr(msg.str());
	this->_inviteOnly = boolean;
}

void Channel::setUserLimit(long unsigned int limit, Client *client)
{
	std::stringstream msg;

	msg << ":" << client->getNick() << " MODE " << this->_name << " ";
	if(limit == MAX_CHANNEL_USER)
		msg << "-l";
	else
		msg << "+l " << limit;
	this->sendStr(msg.str());
	this->_userLimit = limit;
}

void Channel::setTopicOperatorOnly(bool boolean, Client *client)
{
	std::stringstream msg;

	msg << ":" << client->getNick() << " MODE " << this->_name << " ";
	msg << (boolean ? "+t" : "-t");
	this->sendStr(msg.str());
	this->_topicOperatorOnly = boolean;
}
