/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GPTHistory.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:39:41 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/01 14:56:40 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GPTHistory.hpp"

GPTHistory::GPTHistory(std::string name) : _name(name) {}

void GPTHistory::addHistory(std::string role, std::string message)
{
    t_history history;
    
    history.role = role;
    history.message = message;
    _history.push_back(history);
}

std::string GPTHistory::getName() const
{
    return _name;
}

std::vector<t_history> GPTHistory::getHistory() const
{
    return _history;
}

GPTHistory::~GPTHistory() {}