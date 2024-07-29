/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandJoin.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:24:15 by tomoron           #+#    #+#             */
/*   Updated: 2024/07/29 21:24:06 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include.hpp"
#include "commands.hpp"

void commandJoin(const std::string &arg, Client &client, Server &server)
{
	std::vector<std::string>	arg_split;
	std::string channel_name;
	Channel *channel;

	arg_split = ft_split(arg, ' ');
	if(arg_split.size() == 0)
		client.sendInfo(0, 461, "JOIN :Not enough parameters");
	channel_name = arg_split[0];
	channel = server.getChannel(channel_name, 1);
	if(!channel)
		return;
	if(channel->addClient(&client))
	{
		channel->sendStr(":" + client.getIdentifier() + " JOIN " + channel_name);
		if(channel->getTopic().length())
			client.sendInfo(channel, 332, channel->getTopic());
		else
			client.sendInfo(channel, 332, ":No topic is set");
		client.sendInfo(0, 353, "= " + channel_name + " :" + channel->getNames());
		client.sendInfo(0, 366, channel_name + " :End of /NAMES list");
	}
}
