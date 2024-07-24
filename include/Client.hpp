/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:53:55 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/24 14:59:10 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "include.hpp"

class Client
{
	private:
		int			_fd;
		std::string	_user;
		std::string	_nick;
		std::string	_buffer;
		bool		_loggedIn;

		void handleBuffer();

	public:
		Client(int fd);
		~Client(void);

		void		setUser(std::string user);
		void		setNick(std::string nick);
		void		setLoggedIn(bool b);

		std::string	getUser();
		std::string	getNick();
		std::string getBuffer();
		int			getFd();
		bool		getLoggedIn();

		int			updateBuffer();
};




#endif
