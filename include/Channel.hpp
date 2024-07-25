/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:38:54 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/25 21:20:14 by tomoron          ###   ########.fr       */
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
		std::vector<Client*>	_operators;
		std::vector<Client*>	_clients;
		std::vector<Client*>	_invite;
		long unsigned int		_userLimit;

		Channel(void);

	public:
		Channel(std::string name, Client *client);
		~Channel();

		void		setName(std::string name);
		void		setTopic(std::string topic);
		void		setPassword(std::string password);
		void		addOperator(Client *newoperator);

		std::string				getName(void);
		std::string				getTopic(void);
		std::string				getPassword(void);
		std::vector<Client*>	&getClients(void);
		std::vector<Client*>	getOperators();
		std::vector<Client*>	&getInvite(void);
		std::string				getNames();
		bool					isOperator(Client *client);

		int			inviteInChannel(Client &invitor, Client &invited,  Channel &channel);
		int			addClient(Client* client);
		void		delClient(std::string nick);
};


#endif
