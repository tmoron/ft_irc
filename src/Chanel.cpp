/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chanel.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:42:37 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/23 16:48:27 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Chanel.hpp"

Chanel::Chanel(/* args */)
{
}

Chanel::Chanel(std::string name, std::string topic, std::string password) : _name(name), _topic(topic), _password(password)
{
}

void        Chanel::setName(std::string name)
{
    this->_name = name;
}

void        Chanel::setTopic(std::string topic)
{
    this->_topic = topic;
}

void        Chanel::setPassword(std::string password)
{
    this->_password = password;
}

void        Chanel::addClient(Client* client)
{
    if (_clients.size() > 100)
        return ;
        // throw std::exception();
    this->_clients.push_back(client);
}

std::string Chanel::getName(void)
{
    return this->_name;
}

std::string Chanel::getTopic(void)
{
    return this->_topic;
}

std::string Chanel::getPassword(void)
{
    return this->_password;
}

std::vector<Client*> Chanel::getClients(void)
{
    return this->_clients;
}

Chanel::~Chanel()
{
    
}

