/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandWho.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:23:52 by tomoron           #+#    #+#             */
/*   Updated: 2024/07/29 21:19:46 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include.hpp"
#include "commands.hpp"

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
		channel = server.getChannel(arg_split[0], 0);
		if(channel)
			clients = channel->getClients();
		for(unsigned int i = 0; i < clients.size(); i++)
		{
			client.sendInfo(0, 352, clients[i]->getWho(channel));
		}
		client.sendInfo(0, 315, arg_split[0] + " :End of /WHO list");
	}
}
