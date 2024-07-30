/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:32:26 by hubourge          #+#    #+#             */
/*   Updated: 2024/07/30 17:20:35 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_HPP
# define INCLUDE_HPP

extern int g_sig;

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
# include "utils.hpp"
# include <signal.h>
# include <algorithm>
# include <queue>
# include  "AllException.hpp"

# define MAX_MSG_SIZE 50000
# define MAX_CLIENT 100000
# define MAX_CHANNEL_USER 100000

#endif
