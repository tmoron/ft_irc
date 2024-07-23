/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:05:52 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/23 10:36:23 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client() : _nb(0), _name("default"), _buffer("")
{
}

Client::~Client()
{
}

void	Client::setBuffer(std::string buffer)
{
	this->_buffer = buffer;
}

std::string	Client::getBuffer()
{
	return (this->_buffer);
}

void	Client::command(std::string cmd)
{
	std::cout << "Command: " << cmd << std::endl;
}