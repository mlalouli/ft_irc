/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messagerror.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 05:47:27 by mlalouli          #+#    #+#             */
/*   Updated: 2023/04/14 01:01:20 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGERROR_HPP
#define MESSAGERROR_HPP


/******************************/
/*       PassWord Error       */
/******************************/
#define ERR_NEEDMOREPARAMS " :Not enough parameters"
#define ERR_ALREADYREGISTERED " :You may not reregister"
#define ERR_PASSWDMISMATCH " :Password incorrect"
/******************************/
/*       NickName Error       */
/******************************/
#define ERR_ERRONEUSNICKNAME " :Erroneus nickname"
#define ERR_USERONCHANNEL  " :is already on channel"
#define ERR_NICKNAMEINUSE " :Nickname is already in use"
/******************************/
/*         User Error         */
/******************************/
#define ERR_NEEDMOREPARAMS " :Not enough parameters"
#define ERR_ALREADYREGISTERED " :You may not reregister"

#define ERROR " :There is more parameters"
#define ERR_REGISTERED " :You must registred entre command <PASS> <USER> <NICK>"
#define ERR_BADCHANNELKEY " :Cannot join channel"
#define ERR_CHANOPRIVSNEEDED " :You're not channel operator"
/******************************/
/*         INVITE Error       */
/******************************/
#define ERR_NOSUCHNICK " :No such Nickname"
#define ERR_NOSUCHCHANNEL " :No such channel"
#define ERR_USERONCHANNEL " :is already on channel"
#define ERR_USERONCHANNEL " :is already on channel"
/******************************/
/*         Channel Error      */
/******************************/
#define ERR_NOSUCHCHNL " :No such channel"
#define ERR_NOTINCHNL " :You're not on that channel"
#define ERR_USERNOTINCHNL " :They aren't on that channel"
#define ERR_PASSWDMISMATCH " :Password incorrect"
#define ERR_REGISTEREDCHANNEL " :You are reregister in the channel "
#define ERR_BADCHANMASK " :Bad Channel Mask"
#define ERR_NOTCHNLOPER ":You're not channel operator"


#endif