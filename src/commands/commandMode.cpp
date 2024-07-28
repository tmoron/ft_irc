/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandMode.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:36:14 by hubourge          #+#    #+#             */
/*   Updated: 2024/07/29 00:48:54 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include.hpp"
#include "commands.hpp"

int	pushInQueue(std::vector<std::string> &argSplit, std::queue<std::string> &modeQueue, Client &client);

// MODE <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [<ban mask>]
// — i : Définir/supprimer le canal sur invitation uniquement
// — t : Définir/supprimer les restrictions de la commande TOPIC pour les opérateurs de canaux
// — k : Définir/supprimer la clé du canal (mot de passe)
// — o : Donner/retirer le privilège de l’opérateur de canal
// — l : Définir/supprimer la limite d’utilisateurs pour le canal
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

/*--------------------------------- Options ----------------------------------*/
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

/*---------------------------------- Utils -----------------------------------*/
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
