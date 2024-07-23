/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:59:22 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/23 15:13:04 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Command::Command() : _type("none"), _funct(NULL)
{ 
}

Command::Command(std::string type, void (*funct)()) : _type(type), _funct()
{
    
}

Command::~Command()
{
}

void Command::setFunct(void (*funct)())
{
    this->_funct = funct;
}

void        Command::setType(std::string type)
{
    this->_type = type;
}

std::string Command::getType(void)
{
    return this->_type;
}

void        (*Command::getFunct())()
{
    return this->_funct;
}