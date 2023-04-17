/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 01:10:27 by ibenmain          #+#    #+#             */
/*   Updated: 2023/04/14 00:51:21 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "User.hpp"
#include "server.hpp"


User::User(int fd, const std::string& host) : _sd(fd), _host(host), _isQuiting(false) {

}

User::~User() {
    close(_sd);
}

User::User(void){}

int User::getFd(void) const {
    return _sd;
}

const std::string& User::getHost(void) const {
    return _host;
}

std::string User::getPassword(void) {
    return _password;
}

const std::string User::getNickname(void) const {
    if (_nickname.empty()) return "*";

    return _nickname;
}

const std::string User::getSource(void) const {
    std::string source = getNickname();
    if (source.empty()) source = "*";
    source = source + "@" + _host;

    return source;
}

const std::string& User::getUsername(void) const {
    return _username;
}

const std::string& User::getHostname(void) const {
    return _hostname;
}

const std::string& User::getServername(void) const {
    return _servername;
}

const std::string& User::getRealname(void) const {
    return _realname;
}

const std::string& User::getCmdBuffer(void) const {
    return _cmdBuffer;
}

const std::string& User::getReplyBuffer(void) const {
    return _replyBuffer;
}

bool User::getIsQuiting(void) const {
    return _isQuiting;
}

bool User::getIsUser(void) const {
    return _user;
}

bool User::getIsPass(void) const {
    return _pass;
}

bool User::getIsNick(void) const {
    return _nick;
}

const std::string& User::getReason(void) const {
    return _reason;
}

const std::string& User::getChannelLeave(void) const {
    return _channel_leave;
}

void User::setFd(int fd) {
    _sd = fd;
}
void User::setPassword(const std::string& pwd) {
    _password = pwd;
}

void User::setNickname(const std::string& nickname) {
    _nickname = nickname;
}

void User::setUsername(const std::string& username) {
    _username = username;
}

void User::setHostname(const std::string& hostname) {
    _hostname = hostname;
}

void User::setServername(const std::string& servername) {
    _servername = servername;
}

void User::setRealname(const std::string& realname) {
    _realname = realname;
}

void User::setCmdBuffer(const std::string& str) {
    _cmdBuffer = str;
}

void User::clearCmdBuffer(void) {
    _cmdBuffer.clear();
}

void User::setReplyBuffer(const std::string& str) {
    _replyBuffer = str;
}

void User::clearReplyBuffer(void) {
    _replyBuffer.clear();
}

void User::addToCmdBuffer(const std::string& str) {
    _cmdBuffer.append(str);
}

void User::addToReplyBuffer(const std::string& str) {
    _replyBuffer.append(str);
}

void User::setIsQuiting(void) {
    _isQuiting = true;
}

void User::setIsUser(void) {
    _user = true;
}

void User::setIsPass(void) {
    _pass = true;
}

void User::setIsNick(void) {
    _nick = true;
}

int  User::getRegistred(void) const
{
    return (registred);
}

void User::setRegistred(void)
{
    registred = true;
}

void User::setReason(const std::string& reason) {
    _reason = reason;
}

void User::setChannelLeave(const std::string& channel) {
    _channel_leave = channel;
}

User& User::operator=(const User& user)
{
	this->_nickname = user._nickname;
	return(*this);
}

User::User(const User& user)
{
    *this = user;
}

void User::addChannelUser(std::string channel){
	_channelOfUser.push_back(channel);
}

void User::deleteChannelUser(std::string channel){
    std::vector<std::string>::iterator it;

    it = _channelOfUser.begin();
    if (it->find(channel))
        _channelOfUser.erase(it);
}

void User::addChannelOperator(std::string channel){
	_channelOfOperatore.push_back(channel);
}

void User::deleteChannelOperator(std::string channel){
std::vector<std::string>::iterator it;

    it = _channelOfOperatore.begin();
    if (it->find(channel))
        _channelOfOperatore.erase(it);
}

bool User::SearchChannelOperator(std::string channel){

    for (size_t i = 0; i < _channelOfOperatore.size(); i++)
    {
        if (_channelOfOperatore[i] == channel)
            return (true);
    }
    return (false);
}

bool User::SearchChannelUser(std::string channel){

    for (size_t i = 0; i < _channelOfUser.size(); i++)
    {
        if (_channelOfUser[i] == channel)
            return (true);
    }
    return (false);
}

std::string User::ft_hostname()
{
    char hostname[50];

    if (gethostname(hostname, sizeof(hostname)) == -1)
        std::cout << "Error :hostname\n";
    struct hostent *host = gethostbyname(hostname);
    char * szLocalIP;
    szLocalIP = inet_ntoa (*(struct in_addr*)*host->h_addr_list);
    return (szLocalIP);

}

std::vector<std::string> User::getUser()
{
    return (_channelOfUser);

}
std::vector<std::string> User::getChannelList()
{
    return (_channelOfUser);
}
