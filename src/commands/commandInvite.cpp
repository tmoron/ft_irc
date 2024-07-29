/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandInvite.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:25:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/07/29 15:42:15 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include.hpp"
#include "commands.hpp"

void	commandInvite(const std::string &arg, Client &client, Server &server)
{
	std::vector<std::string> arg_split = ft_split(arg, ' ');

	if (arg_split.size() < 2)
	{
		client.sendInfo(0, 461, "INVITE :Not enough parameters");
		return ;
	}
	if (!server.getClient(arg_split[1]))
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
