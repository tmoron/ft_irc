/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:02:43 by copilot           #+#    #+#             */
/*   Updated: 2024/07/24 18:07:43 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandManager.hpp"

/*------------------------------- Constructors -------------------------------*/
CommandManager::CommandManager()
{
}

CommandManager::~CommandManager()
{
}

/*--------------------------------- Methods ----------------------------------*/
CommandManager &CommandManager::addCommand(std::string cmdName, void (*funct)(const std::string &, Client &, Server &))
{
    this->_cmdNames.push_back(cmdName);
    this->_cmdFuncts.push_back(funct);
    return *this;
}

void CommandManager::execCommand(std::string cmdName, const std::string &arg, Client &client, Server &server)
{
	std::cout << "exec command : " << cmdName << std::endl;
	for (size_t i = 0; i < this->_cmdNames.size(); i++)
	{
		if (this->_cmdNames[i] == cmdName)
		{
			this->_cmdFuncts[i](arg, client, server);
			return ;
		}
	}
	std::cout << "unknown command" << std::endl;
	//throw std::exception();
}

void	commandPass(const std::string &pass, Client &clt, Server &srv)
{
	if (srv.getPassword() == pass)
	{
		clt.setLoggedIn(true);
		std::cout << "Client " << clt.getNick() << " as a valid password" << std::endl;
	}
	else // peut etre throw une exeption
		std::cout << "Client " << clt.getNick() << " as a wrong password" << std::endl;
}

void	commandKick(Channel &chnl, Client &clt, std::string msg)
{
	// if (!chnl)
		// ERR_NOSUCHCHANNEL tom erreur ?
	std::vector<Client*> chnlClt = chnl.getClients();
	for (unsigned int i = 0; i < chnlClt.size() - 1; i++)
	{
		if (chnlClt.at(i) == &clt)
		{
			chnlClt.erase(chnlClt.begin() + i);
			if (msg.length() != 0)
				std::cout << msg << std::endl;
			return ;
		}
	}
	// if (i == chnlClt.size())
		// ERR_NOTONCHANNEL tom erreur ?
}

bool	alreadyUse(std::vector<Client*> clients, std::string nick)
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i]->getNick() == nick)
			return true;
	}
	return false;
}

void	commandNick(const std::string &arg, Client &client, Server &server)
{
	std::cout << "nick command" << std::endl;
	if (!alreadyUse(server.getClients(), arg))
		client.setNick(arg);
	else
		throw std::exception();
}

void	commandUser(const std::string &arg, Client &client, Server &server)
{
	std::cout << "user command" << std::endl;
	if (!alreadyUse(server.getClients(), arg))
		client.setUser(arg);
	else
		throw std::exception();
}

void	CommandManager::sendMsgAllClientChannel(std::string msg, std::vector<Client*> cltChnl, Channel &chnl)
{
	for (unsigned int i = 0; i < cltChnl.size(); i++)
	{
		// transmettre le msg au client;
		// cltChnl.at(i);
	}
}
