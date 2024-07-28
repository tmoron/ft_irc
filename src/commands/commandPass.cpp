/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandPass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:27:03 by tomoron           #+#    #+#             */
/*   Updated: 2024/07/29 00:41:27 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include.hpp"
#include "commands.hpp"

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
		clt.setLoggedIn(true);
	else
		clt.sendInfo(0, 464, pass + " :Password incorect" );
}
