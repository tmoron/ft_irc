/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:02:43 by copilot           #+#    #+#             */
/*   Updated: 2024/07/26 17:57:19 by pageblanche      ###   ########.fr       */
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
	return (*this);
}

void CommandManager::execCommand(std::string cmdName, const std::string &arg, Client &client, Server &server)
{
	for (size_t i = 0; i < this->_cmdNames.size(); i++)
	{
		if (this->_cmdNames[i] == cmdName)
		{
			std::cout << "exec command \"" << cmdName << "\"" << std::endl;
			this->_cmdFuncts[i](arg, client, server);
			return ;
		}
	}
	std::cout << "unknown command : \"" << cmdName << "\"" << std::endl;
	client.sendInfo(0, 421, cmdName + std::string(" :Unknown command"));
}

/*--------------------------------- Commands ---------------------------------*/
bool	alreadyUse(std::vector<Client*> &clients, Client *current, std::string nick)
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i]->getNick() == nick && clients[i] != current)
			return true;
	}
	return false;
}

void	sendMsgAllClientChannel(std::string msg, std::vector<Client*> cltChnl, Channel &chnl)
{
	for (unsigned int i = 0; i < cltChnl.size(); i++)
	{
		// transmettre le msg au client;
		// cltChnl.at(i);
	}
}

void	commandPrivMsg(const std::string &arg, Client &client, Server &server)
{
	//flemme (si quelqu'un d'autre vois ça , il y a la methode "sendMessage" pour envoyer un message, j'ai pas testé, j'ai la flemme aussi) // a bas bravo
}

void	commandPass(const std::string &pass, Client &clt, Server &srv)
{
	if(pass.length() == 0)
	{
		clt.sendInfo(0, 461, "PASS :Not enough parameters");
		return ;
	}
	if(clt.isRegistered())
	{
		clt.sendInfo(0, 462, ":You may not reregister");
		return ;
	}
	if (srv.getPassword().compare(pass))
	{
		clt.setLoggedIn(true);
		std::cout << "Client " << clt.getNick() << " as a valid password" << std::endl;
	}
	else
	{
		std::cout << "Client " << clt.getNick() << " as a wrong password" << std::endl;
		clt.sendInfo(0, 464, ":Password incorect" );
	}
}

// KICK <channel> <user> [<comment>]
// KICK &Melbourne Matthew                 ;    Kick Matthew from &Melbourne
// KICK #Finnish John :Speaking English    ;    Kick John from #Finnish using "Speaking English" as the reason (comment).
// :WiZ KICK #Finnish John ; KICK message from WiZ to remove John from channel #Finnish          // ce le suprime peut etre pas ca
void	commandKick(const std::string &arg, Client &client, Server &server)
{
	std::vector<std::string>	argSplit;

	argSplit = ft_split(arg, ' ');
	if(argSplit.size() < 3)
		client.sendInfo(0, 461, "KICK :Not enough parameters");
	if (argSplit[0].find(':')) // jsp il faut se referer a la doc
		return ;

	std::vector<Channel*>		channels = server.getChannels();
	std::vector<std::string>	chnlName = ft_split(argSplit[1], ',');
	std::vector<std::string>	kickName = ft_split(argSplit[2], ',');
	std::string					reasonMsg;

	if (argSplit.size() >= 4)
		reasonMsg = argSplit[3];
	for (unsigned int i = 0; i < channels.size() - 1; i++) // channels available
	{
		for (unsigned int j = 0; j < chnlName.size() - 1; j++) // channel to kick
		{
			if (channels[i]->getName() == chnlName[j]) // channel found
			{
				for (unsigned int k = 0; k < kickName.size() - 1; k++) // people to kick
				{
					if (!channels[i]->isOperator(&client)) // is not operator
					{
						client.sendInfo(0, 482, "KICK :More privileges needed");
						continue ;
					}
					channels[i]->delClient(kickName[k]);
					std::cout << "Kick " << kickName[k] << " from " << channels[i]->getName();
					if (!reasonMsg.empty())
						std::cout << " using " << reasonMsg << std::endl;
				}
			}
		}
	}
}

void	commandInvite(const std::string &arg, Client &client, Server &server)
{
	std::vector<std::string> arg_split = ft_split(arg, ' ');
	if (arg_split.size() < 3)
	{
		client.sendInfo(0, 461, "INVITE :Not enough parameters");
		return ;
	}
	if (alreadyUse(server.getClients(), &client, arg_split[1]))
	{
		client.sendInfo(0, 401, arg_split[1] + " :No such nick/channel");
		return ;
	}
	if (server.getChannel(arg_split[2], 0, 0) == 0)
	{
		client.sendInfo(0, 403, arg_split[2] + " :No such channel");
		return ;
	}
	Channel *chnl = server.getChannel(arg_split[2], 0, 0);
	chnl->inviteInChannel(client, *server.getClient(arg_split[1]), *chnl);
}

void	commandTopic(const std::string &arg, Client &client, Server &server)
{
	std::vector<std::string> arg_split = ft_split(arg, ' ');
	if (arg_split.size() < 2)
	{
		client.sendInfo(0, 461, "TOPIC :Not enough parameters");
		return ;
	}
	if (arg_split.size() == 2 && server.getChannel(arg_split[1], 0, 0))
	{
		//Channel *chnl = server.getChannel(arg_split[1], 0, 0);
		client.sendStr(":localhost 332 #test :coucou");
		// writeMessage(client, 0, 332, chnl->getName() + " :" + chnl->getTopic());
	}
	else if (arg_split.size() >= 3 && server.getChannel(arg_split[1], 0, 0))
	{
		Channel *chnl = server.getChannel(arg_split[1], 0, 0);
		chnl->setTopic(arg_split[2]);
	}
	else
		client.sendInfo(0, 403, arg_split[1] + " :No such channel");
}

void	commandNick(const std::string &arg, Client &client, Server &server)
{
	if(!arg.length())
	{
		client.sendInfo(0, 431, ":No nickname given");
		return ;
	}
	if(!client.getLoggedIn())
		return;
	std::cout << "nick command" << std::endl;
	if (!alreadyUse(server.getClients(), &client, arg))
		client.setNick(arg);
	else
		client.sendInfo(0, 433, arg + " :Nickname is already in use");

}

void	commandUser(const std::string &arg, Client &client, Server &server)
{
	std::vector<std::string> arg_split;

	std::cout << "user command" << std::endl;
	if(client.isRegistered())
	{
		client.sendInfo(0, 462, ":You may not reregister");
		return ;
	}
	arg_split = ft_split(arg, ' ');
	std::cout << "number of args : " << arg_split.size() << std::endl;
	if(arg_split.size() != 4)
		client.sendInfo(0 ,461, "USER :Not enough parameters");
	client.setUser(arg_split[0]);
}

void commandJoin(const std::string &arg, Client &client, Server &server)
{
	std::vector<std::string>	arg_split;
	std::string channel_name;
	Channel *channel;

	arg_split = ft_split(arg, ' ');
	if(arg_split.size() == 0)
		client.sendInfo(0, 461, "JOIN :Not enough parameters");	
	channel_name = arg_split[0];
	channel = server.getChannel(channel_name, &client, 1);
	if(!channel)
		return;
	if(channel->addClient(&client))
	{
		channel->clientJoin(channel_name, client);
		if(channel->getTopic().length())
			client.sendInfo(channel, 332, channel_name + " :" + channel->getTopic());
		else
			client.sendInfo(channel, 332, channel_name + " :No topic is set");
		client.sendInfo(channel, 353, " " + channel_name + " :" + channel->getNames());
		client.sendInfo(channel, 366, channel_name + " :End of /NAMES list");
	}
}

// MODE <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [<ban mask>]
// — i : Définir/supprimer le canal sur invitation uniquement
// — t : Définir/supprimer les restrictions de la commande TOPIC pour les opérateurs de canaux
// — k : Définir/supprimer la clé du canal (mot de passe)
// — o : Donner/retirer le privilège de l’opérateur de canal
// — l : Définir/supprimer la limite d’utilisateurs pour le canal

bool verifOption(std::string option)
{
	std::string		allowedOption = "+-opsitnbv";
	for (size_t i = 0; i < option.length(); i++)
	{
		if (allowedOption.find(option[i]) == std::string::npos)
			return false;
	}
	return true;
}

int	pushInQueue(std::vector<std::string> &argSplit, std::queue<std::string> &modeQueue, Client &client)
{
	for (unsigned int i = 1; i < argSplit.size(); i++)
	{
		if (argSplit[i][0] == '+' || argSplit[i][0] == '-')
		{
			if (verifOption(argSplit[i]))
				modeQueue.push(argSplit[i]);
			else
			{
				client.sendInfo(0, 472, argSplit[i] + " :is unknown mode char to me for " + argSplit[0]);
				return 1;
			}
		}
		else
			modeQueue.push(argSplit[i]);
	}
	return 0;
}

void	commandMode(const std::string &arg, Client &client, Server &server)
{
	std::vector<std::string>	argSplit;

	argSplit = ft_split(arg, ' ');
	if(argSplit.size() < 3)
		client.sendInfo(0, 461, "MODE :Not enough parameters");
	if (server.getChannel(argSplit[0], 0, 0) == 0)
	{
		client.sendInfo(0, 403, argSplit[0] + " :No such channel");
		return ;
	}
	Channel *channel = server.getChannel(argSplit[0], 0, 0);
	std::queue<std::string>	modeQueue;
	if (pushInQueue(argSplit, modeQueue, client))
		return ;
}
