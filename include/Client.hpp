/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:53:55 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/23 11:34:38 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>

class Client
{
	private:
		int			_nb;
		std::string	_user;
		std::string	_nick;
		std::string	_buffer;

	public:
		Client(void);
		Client(std::string user, std::string nick);
		~Client(void);
		
		void		setBuffer(std::string buffer);
		void		setUser(std::string user);
		void		setNick(std::string nick);
		std::string	getUser();
		std::string	getNick();
		std::string	getBuffer();
};




#endif
