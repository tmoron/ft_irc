/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandUser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:24:30 by tomoron           #+#    #+#             */
/*   Updated: 2024/08/02 16:11:10 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include.hpp"
#include "commands.hpp"

void	commandUser(const std::string &arg, Client &client, Server &server)
{
	std::vector<std::string> arg_split;

	if(!client.getLoggedIn())
		return;
	if(client.isRegistered())
	{
		client.sendInfo(0, 462, ":You may not reregister");
		return ;
	}
	arg_split = ft_split(arg, ' ');
	if(arg_split.size() != 4)
	{
		client.sendInfo(0 ,461, "USER :Not enough parameters");
		return ;
	}
	client.setUser(arg_split[0]);
	client.setHostname(arg_split[1]);
	client.setServername(arg_split[2]);
	client.setRealname(arg_split[3]);
}
