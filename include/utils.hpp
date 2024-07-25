/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:29:50 by tomoron           #+#    #+#             */
/*   Updated: 2024/07/25 15:45:23 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

#include "include.hpp"

std::string					trim(char c, std::string str);
std::vector<std::string>	ft_split(std::string str, char c);
void Handler(int signum);

#endif
