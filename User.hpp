/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 01:10:38 by ibenmain          #+#    #+#             */
/*   Updated: 2023/04/14 00:49:58 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP
# include <string>
# include <vector>

class User {
	public:
		int _sd;
		bool _pass;
		bool _user;
		bool _nick;
		bool registred;
		std::string _host;
		std::string _password;
		std::string _nickname;
		std::string _username;
		std::string _hostname;
		std::string _servername;
		std::string _realname;
		std::string _cmdBuffer;
		std::string _replyBuffer;
		std::string _reason;
		std::string _channel_leave;
		bool _isQuiting;
		std::vector<std::string> _channelOfUser;
		std::vector<std::string> _channelOfOperatore;

	public:
		User(void);
		User(const User& user);
		User& operator=(const User& user);
        User(int fd, const std::string& host);
		~User();
		void addChannelUser(std::string channel);
		void addChannelOperator(std::string channel);
		void deleteChannelUser(std::string channel);
		void deleteChannelOperator(std::string channel);
		bool SearchChannelOperator(std::string channel);
		bool SearchChannelUser(std::string channel);
		int getFd(void) const;
		const std::string& getHost(void) const;
		std::string getPassword(void);
		const std::string getNickname(void) const;
		const std::string getSource(void) const;
		const std::string& getUsername(void) const;
		const std::string& getHostname(void) const;
		const std::string& getServername(void) const;
		const std::string& getRealname(void) const;
		const std::string& getCmdBuffer(void) const;
		const std::string& getReplyBuffer(void) const;
		bool getIsQuiting(void) const;
		bool getIsUser(void) const;
		bool getIsPass(void) const;
		bool getIsNick(void) const;
		int  getRegistred(void) const;
		const std::string& getReason(void) const;
		const std::string& getChannelLeave(void) const;

		void setPassword(const std::string& pwd);
		void setNickname(const std::string& nickname);
		void setUsername(const std::string& username);
		void setHostname(const std::string& hostname);
		void setServername(const std::string& servername);
		void setRealname(const std::string& realname);
		void setIsQuiting(void);
		void setIsUser(void);
		void setIsPass(void);
		void setIsNick(void);
		void setRegistred(void);
		void setFd(int fd);
		void setReason(const std::string& reason);
		void setChannelLeave(const std::string& channel);

		void setCmdBuffer(const std::string& src);
		void clearCmdBuffer(void);
		void setReplyBuffer(const std::string& src);
		void clearReplyBuffer(void);
		void addToCmdBuffer(const std::string& src);
		void addToReplyBuffer(const std::string& src);
		std::string ft_hostname();
		std::vector<std::string> getUser();
		std::vector<std::string> getChannelList();

};

#endif
