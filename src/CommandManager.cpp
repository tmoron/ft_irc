/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:02:43 by copilot           #+#    #+#             */
/*   Updated: 2024/07/27 02:03:06 by tomoron          ###   ########.fr       */
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
			this->_cmdFuncts[i](arg, client, server);
			return ;
		}
	}
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
	std::vector<std::string> arg_split;
	Channel *channel;

	arg_split = ft_split_irc(arg);
	if(arg_split.size() == 0)
	{
		client.sendInfo(0, 411, ":No recipient given PRIVMSG");
		return;
	}
	if(arg_split.size() == 1)
	{
		client.sendInfo(0, 412, ":No text to send");
		return;
	}
	if(arg_split[0][0] == '#')
	{
		channel = server.getChannel(arg_split[0], 0 ,0);
		if(!channel)
		{
			client.sendInfo(0, 404, arg_split[0] + " :Cannot send to channel");
			return;
		}
		channel->sendMsg(client, arg_split[1]);
	}
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
	if (srv.getPassword() == pass)
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
	if (!alreadyUse(server.getClients(), &client, arg))
		client.setNick(arg);
	else
		client.sendInfo(0, 433, arg + " :Nickname is already in use");

}

void	commandUser(const std::string &arg, Client &client, Server &server)
{
	std::vector<std::string> arg_split;

	if(client.isRegistered())
	{
		client.sendInfo(0, 462, ":You may not reregister");
		return ;
	}
	arg_split = ft_split(arg, ' ');
	if(arg_split.size() != 4)
		client.sendInfo(0 ,461, "USER :Not enough parameters");
	client.setUser(arg_split[0]);
	client.setHostname(arg_split[1]);
	client.setServername(arg_split[2]);
	client.setRealname(arg_split[3]);
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
			client.sendInfo(channel, 332, ":" + channel->getTopic());
		else
			client.sendInfo(channel, 332, ":No topic is set");
		//client.sendStr(":localhost 353 = #test :@tom");
		client.sendInfo(0, 353, "= " + channel_name + " :" + channel->getNames());
		client.sendInfo(0, 366, channel_name + " :End of /NAMES list");
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
	std::string		allowedOption = "+-itkol";
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

void	commandModeI(const std::string &arg, Client &client, Server &server, Channel &chnl, std::string &cmdOpt)
{
	if (chnl.isOperator(&client))
	{
		client.sendInfo(0, 482, "MODE :More privileges needed");
		return ;
	}
	if (cmdOpt[0] == '+')
	{
		client.sendInfo(0, 324, ":Channel mode is invite only");
		chnl.setInviteOnly(true);
	}
	else if (cmdOpt[0] == '-')
	{
		client.sendInfo(0, 324, ":Channel mode is not invite only");
		chnl.setInviteOnly(false);
	}
}

void	commandModeT(const std::string &arg, Client &client, Server &server, Channel &chnl, std::string &cmdOpt)
{
	if (chnl.isOperator(&client))
	{
		client.sendInfo(0, 482, "MODE :More privileges needed");
		return ;
	}
	if (cmdOpt[0] == '+')
	{
		client.sendInfo(0, 324, ":Channel mode is topic operator only");
		chnl.setTopicOperatorOnly(true);
	}
	else if (cmdOpt[0] == '-')
	{
		client.sendInfo(0, 324, ":Channel mode is not topic operator only");
		chnl.setTopicOperatorOnly(false);
	}
}

void	commandModeK(const std::string &arg, Client &client, Server &server, Channel &chnl, std::string &cmdOpt, std::string &cmdArg)
{
	if (chnl.isOperator(&client))
	{
		client.sendInfo(0, 482, "MODE :More privileges needed");
		return ;
	}
	if (cmdOpt[0] == '-')
	{
		client.sendInfo(0, 0, ":Unset the channel key"); // trouver le bon code
		chnl.setPassword("");
	}
	else if (chnl.getPassword() != "")
	{
		client.sendInfo(0, 467, ":Channel key is already set");
		return ;
	}
	else if (cmdOpt[0] == '+')
	{
		client.sendInfo(0, 0, ":Set the channel key to " + cmdArg); // trouver le bon code
		chnl.setPassword(cmdArg);
	}
}

void	commandModeO(const std::string &arg, Client &client, Server &server, Channel &chnl, std::string &cmdOpt)
{
	if (chnl.isOperator(&client))
	{
		client.sendInfo(0, 482, "MODE :More privileges needed");
		return ;
	}
	if (cmdOpt[0] == '+')
	{
		client.sendInfo(0, 324, ":Channel mode is topic operator only");
		chnl.setTopicOperatorOnly(true);
	}
	else if (cmdOpt[0] == '-')
	{
		client.sendInfo(0, 324, ":Channel mode is not topic operator only");
		chnl.setTopicOperatorOnly(false);
	}
}

void	commandModeL(const std::string &arg, Client &client, Server &server, Channel &chnl, std::string &cmdOpt, std::string &cmdArg)
{
	if (chnl.isOperator(&client))
	{
		client.sendInfo(0, 482, "MODE :More privileges needed");
		return ;
	}
	if (cmdOpt[0] == '+')
	{
		client.sendInfo(0, 324, ":Set the channel limit to " + arg);
		if (stdStringToLongUnsignedInt(cmdArg) > MAX_CHANNEL_USER)
			chnl.setUserLimit(MAX_CHANNEL_USER);
		else
			chnl.setUserLimit(stdStringToLongUnsignedInt(cmdArg));
	}
	else if (cmdOpt[0] == '-')
	{
		client.sendInfo(0, 324, ":Unset the channel limit");
	}
}

void commandWho(const std::string &arg, Client &client, Server &server)
{
	std::vector<std::string> arg_split;
	std::vector<Client *> clients;
	Channel *channel;

	arg_split = ft_split(arg, ' ');
	if(arg_split.size() < 1)
	{
		client.sendInfo(0, 461, "WHO :Not enough parameters");
		return;
	}
	if(arg_split.size() > 1)
		return;
	if(arg_split[0][0] == '#')
	{
		channel = server.getChannel(arg_split[0], 0 , 0);
		if(channel)
			clients = channel->getClients();
		for(unsigned int i = 0; i < clients.size(); i++)
		{
			client.sendInfo(0, 352, clients[i]->getWho(channel));
		}
		client.sendInfo(0, 315, arg_split[0] + " :End of /WHO list");
	}
}

void commandPing(const std::string &arg, Client &client, Server &server)
{
	client.sendStr(":localhost PONG " + arg);
}
