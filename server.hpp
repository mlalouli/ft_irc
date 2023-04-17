/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 05:46:54 by mlalouli          #+#    #+#             */
/*   Updated: 2023/04/14 00:49:55 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SERVER_HPP
# define SERVER_HPP

# include <cstring>
# include <ctime>
# include <map>
# include <exception>
#include <iostream>
# include <sys/types.h>
# include <sys/event.h>
# include <sys/time.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <vector>
#include <netdb.h>
#include <sstream>

class User;
class Channel;
class Server {
    public:
        int _sd;
        int _kq;
        int _port;
        std::string _password;
        std::string _command;
        std::vector<std::string> _params;
        std::map<int, User *> _allUser;
        std::map<std::string, Channel *> _allChannel;
        std::vector<struct kevent> eventList;
        struct kevent _waitingEvents[8];

    public:
        Server(void);
        Server(const Server& server);
        const std::vector<std::string>& getParams(void) const;
        const std::string& getCommand(void) const;
        void updateEvents(int socket, int16_t filter, uint16_t flags, uint32_t fflags, intptr_t data, void *udata);
        std::string getpassword();
        void createNewClientSocket(void);
        Server(int port, std::string password);
        void recvClientData(const struct kevent& event);
        void sendDataToClient(const struct kevent& event);
        void handleEvent(const struct kevent& event);
        void run(void);
        void shutDown(const std::string& msg);
        void __parssingCommand(User* user, const struct kevent& event);
        void checkPassword(std::vector<std::string> tab, User* user, const struct kevent& event);
        void sendMessage(const struct kevent& event, std::string msg);
        void checkUser(std::vector<std::string> tab, User* user, const struct kevent& event);
        void checkNick(std::vector<std::string> tab, User* user, const struct kevent& event);
        void authentication(std::vector<std::string> tab, User* user, const struct kevent& event);
        void sendMessageWelcom(std::string buffer, User* user, const struct kevent& event);
        int  checkUserExist(std::vector<std::string> tab, User* user, const struct kevent& event);
        int	 checkNickExist(std::vector<std::string> tab, User* user, const struct kevent& event);
        void handleCmd(User *user, const struct kevent& event);
        size_t checkCmd(User *user);
        void findCmd(std::string cmd);
        std::vector<std::string> split(const std::string& str, const char delimeter);
        User* findClientByNickname(const std::string& nickname) const;
        Channel* findChannelByName(const std::string& name) const;
        Channel* addChannel(const std::string& name);
        void deleteChannel(const std::string& name);
        void cmdInvite(User *user, const struct kevent event, std::vector<std::string> invite);
        void sendMessage_error(std::string nickname, const struct kevent& event, std::string msg, int code);
        const std::string createReplyForm(User *user) const;
        void cmdPrivmsg(User *user, const struct kevent& event);
        void cmdJoin(User *user, const struct kevent& event, std::vector<std::string> channel);
        void cmdPart(User *user, const struct kevent& event, std::vector<std::string> tab);
        void cmdMode(User *user, const struct kevent& event, std::vector<std::string> tab);
        void cmdTopic(User *user, const struct kevent& event, std::vector<std::string> tab);
        void cmdQuit(User *user, const struct kevent& event, std::vector<std::string> tab);
        void cmdNotice(User *user, const struct kevent& event);
        void cmdKick(User *user, const struct kevent& event);
        bool getUesrNickname(std::string nickname);
        void boot(const struct kevent& event);
        void sendMessage_bot(std::string nickname, const struct kevent& event);
};

#endif