/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:02:43 by copilot           #+#    #+#             */
/*   Updated: 2024/07/24 15:05:02 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandManager.hpp"

CommandManager::CommandManager()
{
}

CommandManager &CommandManager::addCommand(std::string cmdName, void (*funct)(const std::string &, Client &, Server &))
{
    this->_cmdNames.push_back(cmdName);
    this->_cmdFuncts.push_back(funct);
    return *this;
}

void CommandManager::execCommand(std::string cmdName, const std::string &arg, Client &client, Server &server)
{
	for (size_t i = 0; i < this->_cmdNames.size(); i++)
	{
		if (this->_cmdNames[i] == cmdName)
		{
			this->_cmdFuncts[i](arg, client, server);
			return ;
		}
	}
	throw std::exception();
}


CommandManager::~CommandManager()
{
}

void	CommandManager::commandPass(std::string pass, Client &clt, Server &srv)
{
	if (srv.getPassword() == pass)
	{
		clt.setLoggedIn(true);
		std::cout << "Client " << clt.getNick() << " as a valid password" << std::endl;
	}
	else
		std::cout << "Client " << clt.getNick() << " as a wrong password" << std::endl;
}
