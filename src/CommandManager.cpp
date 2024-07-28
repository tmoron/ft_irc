/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:02:43 by copilot           #+#    #+#             */
/*   Updated: 2024/07/29 00:28:10 by tomoron          ###   ########.fr       */
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
CommandManager &CommandManager::addCommand(std::string cmdName, void (*funct)(const std::string &, Client &, Server &), bool requireRegister)
{
	this->_cmdNames.push_back(cmdName);
	this->_cmdFuncts.push_back(funct);
	this->_cmdRequireRegister.push_back(requireRegister);
	return (*this);
}

void CommandManager::execCommand(std::string cmdName, const std::string &arg, Client &client, Server &server)
{
	for (size_t i = 0; i < this->_cmdNames.size(); i++)
	{
		if (this->_cmdNames[i] == cmdName)
		{
			if(this->_cmdRequireRegister[i] && !client.isRegistered())
				client.sendInfo(0, 451, ":You have not registered");
			else
				this->_cmdFuncts[i](arg, client, server);
			return ;
		}
	}
	client.sendInfo(0, 421, cmdName + std::string(" :Unknown command"));
}
