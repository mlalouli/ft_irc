/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 01:11:04 by ibenmain          #+#    #+#             */
/*   Updated: 2023/04/15 17:08:11 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include "Channel.hpp"
#include "server.hpp"

Channel::Channel(void){}
Channel::Channel(const std::string& name){
    _name = name;
    _password = "";
    _nametopic = "";
    _findPass = 0;
    _topic = 0;
    _invit = 0;
}

Channel::Channel(std::string name, std::string password){
    _name = name;
    _password = password;
    _nametopic = "";
    _findPass = 0;
    _topic = 0;
    _invit = 0;
};

Channel::~Channel() { }

const std::string& Channel::getName(void) const {
    return _name;
}

void Channel::broadcast(User *user ,Server *server, std::string option, int flag) const {
    std::map<int, User *>::const_iterator it;
    const std::string msg = server->createReplyForm(user);

    for(it = _userList.begin(); it != _userList.end(); ++it) {
        if (it->second->getNickname() == user->getNickname() && flag == 0) continue;
        if (flag == 0)
            it->second->addToReplyBuffer(server->createReplyForm(user));
        else if (flag == 1)
            it->second->addToReplyBuffer(":"+user->getNickname()+"!"+user->getUsername()+"@"+user->getHost()+ " JOIN :" + user->getChannelList().back() + "\n");
        else if (flag == 2) {
            it->second->addToReplyBuffer(":"+user->getNickname()+"!"+user->getUsername()+"@"+user->getHost()+ " PART " + user->getChannelLeave() + (user->getReason().empty() ? "" : (" :" + user->getReason())) + "\n");
        }
        else if (flag == 3) {
            it->second->addToReplyBuffer(":" + (user->getUsername().empty() ? "" : (user->getNickname() + "!" + user->getUsername())) + "@" + user->getHost() + option + "\n");
        }
    }
}

const std::vector<std::string> Channel::getUserList(void) const {
    std::vector<std::string> userList;

    for (std::map<int, User *>::const_iterator it = _userList.begin(); it != _userList.end(); ++it) {
        std::string nickname = "";
        nickname += it->second->getNickname();
        userList.push_back(nickname);
    }
    return userList;
}

void    Channel::setOperator()
{
    std::map<int, User *>::iterator it;
    it = _operators.begin();
    for (; it != _operators.end(); it++)
        it->second->setNickname("@" + it->second->getNickname());   
}

void Channel::addUser(int clientFd, User *user) {
    _userList.insert(std::make_pair(clientFd, user));
}

void Channel::addOperators(int clientFd, User *user) {
    _operators.insert(std::make_pair(clientFd, user));
}

int Channel::deleteUser(int clientFd) {
    std::map<int, User *>::iterator it;

    it = _userList.find(clientFd);
    if (it == _userList.end()) return _userList.size();
    {
        _userList.erase(it);
    }
    if (_userList.empty()) return 0;
    return _userList.size();
}

void Channel::deleteOperator(int clientFd) {
    std::map<int, User *>::iterator it;

    it = _operators.find(clientFd);
    if (it != _operators.end())
    {
        _operators.erase(it);
    }
}

User* Channel::findUserByFd(const int clientFd) {
    std::map<int, User *>::iterator it;

    it = _userList.find(clientFd);
    if (it == _userList.end()) return NULL;
    return it->second;
}

User* Channel::findFirstUserbyNick(std::string nick) {
    std::map<int, User *>::iterator it;

    it = _userList.begin();
    for (; it != _userList.end(); it++)
    {
        if (it->second->getNickname() == nick)
            return (it->second);
    }
    if (it == _userList.end()) return NULL;
    return it->second;
}

User* Channel::findSecondUser(std::string nick) {
    std::map<int, User *>::iterator it;
    for (it = _userList.begin() ; it != _userList.end(); it++)
    {
        if (it->second->getNickname() != nick)
            return(it->second);
    }
    return (NULL);
}

bool Channel::findOperatorIfExistByNick(std::string nick) {
    std::map<int, User *>::iterator it;
    it = _operators.begin();
    for (; it != _operators.end(); it++)
    {
        if (it->second->getNickname() == nick)
            return (true);
    }
    return (false);
}

bool Channel::findUserIfExistByNick(std::string nick) {
    std::map<int, User *>::iterator it;
    it = _userList.begin();
    for (; it != _userList.end(); it++)
    {
        if (it->second->getNickname() == nick)
            return (true);
    }
    return (false);
}

int Channel::getFdOfUser(std::string nick) {
    std::map<int, User *>::iterator it;
    it = _userList.begin();
    for (; it != _userList.end(); it++)
    {
        if (it->second->getNickname() == nick)
            return (it->first);
    }
    return (false);
}

int Channel::getFdOfOperator(std::string nick) {
    std::map<int, User *>::iterator it;
    it = _operators.begin();
    for (; it != _operators.end(); it++)
    {
        if (it->second->getNickname() == "@" + nick)
            return (it->first);
    }
    return (false);
}

bool Channel::findOperatorIfExist(const int clientFd) {
    std::map<int, User *>::iterator it;

    it = _operators.find(clientFd);
    if (it != _operators.end())
        return (true);
    return (false);
}

bool Channel::findUserIfExistByFd(const int clientFd) {
    std::map<int, User *>::iterator it;

    it = _userList.find(clientFd);
    if (it != _userList.end())
        return (true);
    return (false);
}

User* Channel::findUserByNick(const std::string& nickname) {
    std::map<int, User *>::iterator it;

    for(it = _userList.begin(); it != _userList.end(); ++it) {
        User *user = it->second;

        if (user->getNickname() == nickname) return user;
    }
    return NULL;
}

std::vector<std::string>   Channel::getAllUser()
{
    std::vector<std::string> vect;
    std::map<int, User *>::iterator it;
    it = _userList.begin();
    for (; it != _userList.end(); it++)
    {
        if (isOperator(it->second))
            vect.push_back("@" + it->second->getNickname());
        else
            vect.push_back(it->second->getNickname());
    }
    return (vect);
}

const std::string    Channel::getUser(int fd)
{
    std::map<int, User *>::iterator it;
    it = _userList.find(fd);
    return(it->second->getNickname());
}

void    Channel::getInvite(void)
{
    for (size_t i = 0; i < _invite.size(); i++)
        std::cout << "Invite: " << _invite[i] << std::endl;
}

std::string    Channel::getSecondOperator(void)
{
     std::map<int, User *>::iterator it;

    it = _userList.begin();
    return(it->second->getNickname());
}

bool Channel::getFindPass() const
{
    return (_findPass);
}

void Channel::setFindPass(bool pass)
{
    _findPass = pass;
}

bool Channel::getTopic() const
{
    return (_topic);
}

void Channel::setTopic(bool topic)
{
    _topic = topic;
}

bool Channel::getFoundtopic() const
{
    return (_foundtopic);
}

void Channel::setFoundtopic(bool foundtopic)
{
    _foundtopic = foundtopic;
}

std::string Channel::getNametopic()
{
    return (_nametopic);
}

void Channel::setNametopic(std::string nametopic)
{
    _nametopic = nametopic;
}

bool Channel::getInvit() const
{
    return (_invit);
}

void Channel::setInvit(bool invit)
{
    _invit = invit;
}

std::string Channel::getPassword() const
{
    return (_password);
}

void Channel::editPassword(std::string passwd)
{
    _password = passwd;
}

std::string Channel::getPassword(void)
{
    return(_password);
}

void Channel::deletePassword()
{
    _password.clear();
}

bool Channel::isOperator(User *user){
    for (std::map<int, User *>::const_iterator it = _operators.begin(); it != _operators.end(); ++it){
        if (user->getNickname() == (*it).second->getNickname()){
            return true;
        }
    }
    return false;
}

int Channel::checkInvit(std::string nick)
{
    for (size_t i = 0; i < _invite.size(); i++)
    {
      if (_invite[i] == nick)
        return(1);
    }
    return (0);
}

void Channel::deleteInvite(std::string nickname)
{
  std::vector<std::string>::iterator it;

  it = find(_invite.begin(), _invite.end(), nickname);
    if (it != _invite.end())
        _invite.erase(it);
}