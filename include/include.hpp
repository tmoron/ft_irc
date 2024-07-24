/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:32:26 by hubourge          #+#    #+#             */
/*   Updated: 2024/07/24 20:58:31 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_HPP
# define INCLUDE_HPP

# include <sys/socket.h>
# include <netinet/in.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdint.h>
# include <poll.h>
# include <stdio.h>
# include <iostream>
# include <sstream>
# include <string>
# include <vector>
# include <exception>
# include "utils.hpp"


# define MAX_MSG_SIZE 50000
# define MAX_CLIENT 100

#endif
