/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chanel.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:38:54 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/23 16:49:38 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANEL_HPP
# define CHANEL_HPP

#include <string>
#include <vector>
#include "Client.hpp"

class Chanel
{
private:
    std::string _name;
    std::string _topic;
    std::string _password;
    std::vector<Client*> _clients;
    Chanel(/* args */);
    
public:
    Chanel(std::string name, std::string topic, std::string password);

    void        setName(std::string name);
    void        setTopic(std::string topic);
    void        setPassword(std::string password);
    void        addClient(Client* client);
    std::string getName(void);
    std::string getTopic(void);
    std::string getPassword(void);
    std::vector<Client*> getClients(void);
    
    ~Chanel();
};


#endif