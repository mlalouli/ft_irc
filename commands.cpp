/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 01:10:59 by ibenmain          #+#    #+#             */
/*   Updated: 2023/04/14 00:51:21 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "User.hpp"
#include "messagerror.hpp"
#include "Channel.hpp"

void Server::cmdNotice(User *user, const struct kevent& event) {
    if (_params.size() < 2) {
		sendMessage_error(user->getNickname(), event, ERR_NEEDMOREPARAMS, 461);
		return;
	}

    const std::vector<std::string> targetList = split(getParams()[0], ',');
    for (std::vector<std::string>::const_iterator it = targetList.begin(); it != targetList.end(); ++it) {
        std::string targetName = *it;
    	Channel *targetChannel;

        targetChannel = findChannelByName(targetName);
        if (targetChannel == NULL) {
			sendMessage_error(user->getNickname(), event, ERR_NOSUCHCHNL, 401);
			continue;
		}
		targetChannel->broadcast(user , this, "", 0);
    }
}

void Server::cmdKick(User *user, const struct kevent& event){
	if (_params.size() < 2) {
		sendMessage(event, ERR_NEEDMOREPARAMS);
		return;
	}

	if (_params.size() == 2) {

		if ((_params[0][0] != '#' && _params[0][0] != '&') || (_params[0].size() == 1 && (_params[0][0] == '#' || _params[0][0] == '&')))
			sendMessage(event, " :Bad Channel Mask");

		Channel *targetChannel = findChannelByName(_params[0]);
		if (targetChannel == NULL) {
			sendMessage(event, ERR_NOSUCHCHNL);
			return;
		}

		if (targetChannel->findUserByFd(user->getFd()) == NULL){
			sendMessage(event, ERR_NOTINCHNL);
			return;
		}

		if (targetChannel->isOperator(user) == false){
			sendMessage(event, ERR_NOTCHNLOPER);
			return;
		}

		const std::vector<std::string> targetUsers = split(_params[1], ',');
		for (std::vector<std::string>::const_iterator it = targetUsers.begin(); it != targetUsers.end(); ++it) {
			
			User *targetUser = targetChannel->findUserByNick(*it);
			if (targetUser == NULL) {
				sendMessage(event, ERR_USERNOTINCHNL);
				continue;
			}

			int flag = targetChannel->deleteUser(targetUser->getFd());
			targetChannel->broadcast(user, this, " KICK " + targetChannel->getName() + " " + targetUser->getNickname(), 3);
			if (flag == 0) {
				deleteChannel(targetChannel->getName());
			}
		}
	}
}

void	Server::sendMessage_error(std::string nickname, const struct kevent& event, std::string msg, int code)
{
	int sendBytes;
	std::string name;
	std::stringstream ss;
	
	ss << code;
	name = ss.str()  + " " + nickname + msg + "\n";
	sendBytes = send(event.ident, name.c_str(), name.size(), 0);
	if (sendBytes <= 0) {
		std::cerr << "client send error!" << std::endl;
		_allUser.erase(event.ident);
		std::cout << "client disconnected: " << event.ident << '\n';
		return;
	}
}

void Server::cmdInvite(User *user, const struct kevent event, std::vector<std::string> invite)
{
	std::map<std::string, Channel *>::iterator it;
	std::string nickname = invite[0];
	std::string channel = invite[1];

	if (invite.size() != 2)
		return(sendMessage_error(user->getNickname(), event, ERR_NEEDMOREPARAMS, 461));
	it = _allChannel.find(channel);
	if (it != _allChannel.end())
	{
		if (it->second->getInvit() == 1 && it->second->findOperatorIfExist(user->getFd()))
		{
			if (getUesrNickname(nickname))
				it->second->_invite.push_back(nickname);
			else
				return(sendMessage_error(nickname, event, " :User not found", 401));
		}
		else if (it->second->getInvit() == 0 && it->second->findUserIfExistByFd(user->getFd()))
		{
			if (getUesrNickname(nickname))
				it->second->_invite.push_back(nickname);
			else
				return(sendMessage_error(nickname, event, " :User not found", 401));
		}
		else
			return (sendMessage_error(nickname, event, " :User not member in the channel", 401));
	}
	else
		return (sendMessage_error(nickname, event, ERR_NOSUCHCHANNEL, 403));
}
