/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:38:54 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/25 18:24:53 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Channel_HPP
# define Channel_HPP

# include <string>
# include <vector>
# include "Client.hpp"

class Channel
{
	private:
		std::string				_name;
		std::string				_topic;
		std::string				_password;
		Client					*_operator;
		std::vector<Client*>	_clients;
		std::vector<Client*>	_invite;
		Channel(void);

	public:
		Channel(std::string name, Client *client);
		~Channel();

		void		setName(std::string name);
		void		setTopic(std::string topic);
		void		setPassword(std::string password);
		void		setOperator(Client *newoperator);

		std::string				getName(void);
		std::string				getTopic(void);
		std::string				getPassword(void);
		std::vector<Client*>	&getClients(void);
		Client					*getOperator();
		std::vector<Client*>	&getInvite(void);

		int			inviteInChannel(Client &invitor, Client &invited,  Channel &channel);
		void		addClient(Client* client);
};


#endif
