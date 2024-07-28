/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandTopic.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:25:13 by tomoron           #+#    #+#             */
/*   Updated: 2024/07/29 00:41:27 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include.hpp"
#include "commands.hpp"

void	commandTopic(const std::string &arg, Client &client, Server &server)
{
	std::vector<std::string> arg_split = ft_split_irc(arg);
	if (arg_split.size() < 1)
	{
		client.sendInfo(0, 461, "TOPIC :Not enough parameters");
		return ;
	}
	if (arg_split.size() == 1 && server.getChannel(arg_split[0], 0, 0))
	{
		Channel *chnl = server.getChannel(arg_split[0], 0, 0);
		if(chnl->getTopic().length())
			client.sendInfo(chnl, 332, chnl->getTopic());
		else
			client.sendInfo(chnl, 332, ":No topic is set");
	}
	else if (arg_split.size() >= 2 && server.getChannel(arg_split[0], 0, 0))
	{
		Channel *chnl = server.getChannel(arg_split[0], 0, 0);
		chnl->setTopic(arg_split[1]);
		chnl->sendStr(":" + client.getNick() + " TOPIC " + arg_split[0] + " " + arg_split[1]);
	}
	else
		client.sendInfo(0, 403, arg_split[0] + " :No such channel");
}
