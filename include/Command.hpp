/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:20:42 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/23 16:52:32 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<string>

#ifndef COMMAND_HPP
#define COMMAND_HPP

class Command
{
	private:
		std::string	_type;
		void		(*_funct)();
	public:
		Command();
		Command(std::string type, void (*funct)());

		void		setFunct(void (*_funct)());
		void		setType(std::string type);
		void		(*getFunct())();
		std::string	getType(void);
		~Command();
};

#endif
