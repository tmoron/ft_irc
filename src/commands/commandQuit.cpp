/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandQuit.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 23:38:34 by tomoron           #+#    #+#             */
/*   Updated: 2024/07/29 23:53:02 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"
#include "include.hpp"

void commandQuit(const std::string &arg, Client &client, Server &server)
{
	client.quit();
}
