/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:53:55 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/22 16:17:05 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <string>

class Client
{
    private:
        int         nb;
        std::string _name;
        std::string _buffer;
        Client(/* args */);
    public:
        ~Client();
};



#endif
