/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandInvite.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:25:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/07/30 19:11:07 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include.hpp"
#include "commands.hpp"

void	commandInvite(const std::string &arg, Client &client, Server &server)
{
	std::vector<std::string> arg_split = ft_split(arg, ' ');
	Client *invited;

	if (arg_split.size() < 2)
	{
		client.sendInfo(0, 461, "INVITE :Not enough parameters");
		return ;
	}
	invited = server.getClient(arg_split[0]);
	if (!invited)
	{
		client.sendInfo(0, 401, arg_split[0] + " :No such nick/channel");
		return ;
	}
	Channel *chnl = server.getChannel(arg_split[1], 0);
	if (!chnl)
	{
		client.sendInfo(0, 403, arg_split[1] + " :No such channel");
		return ;
	}
	if (chnl->getInviteOnly() && !chnl->isOperator(&client))
	{
		client.sendInfo(chnl, 482, ":You're not channel operator");
		return ;
	}
	std::string str = ":" + client.getNick() + " INVITE " + invited->getNick() + " " + chnl->getName();
	chnl->sendStr(str);
	chnl->inviteInChannel(client, *invited);

}
