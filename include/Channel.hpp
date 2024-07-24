/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:38:54 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/24 17:49:07 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Channel_HPP
# define Channel_HPP

#include <string>
#include <vector>
#include "Client.hpp"

class Channel
{
    private:
        std::string _name;
        std::string _topic;
        std::string _password;
        std::vector<Client*> _clients;
        Channel(/* args */);

    public:
        Channel(std::string name, std::string topic, std::string password);
        ~Channel();

        void        setName(std::string name);
        void        setTopic(std::string topic);
        void        setPassword(std::string password);
        void        addClient(Client* client);

        std::string getName(void);
        std::string getTopic(void);
        std::string getPassword(void);
        std::vector<Client*> &getClients(void);

};


#endif
