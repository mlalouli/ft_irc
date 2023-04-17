/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boot.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlalouli <mlalouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:00:35 by mlalouli          #+#    #+#             */
/*   Updated: 2023/04/17 21:00:39 by mlalouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "User.hpp"
#include "messagerror.hpp"
#include "Channel.hpp"

void	Server::sendMessage_bot(std::string nickname, const struct kevent& event)
{
	int sendBytes;
	std::string name = nickname;
	name = name + "\n";
	sendBytes = send(event.ident, name.c_str(), name.size(), 0);
	if (sendBytes <= 0) {
		std::cerr << "client send error!" << std::endl;
		_allUser.erase(event.ident);
		std::cout << "client disconnected: " << event.ident << '\n';
		return;
	}
}

void Server::boot(const struct kevent& event) {
    // Create an array of messages
    std::string messages[] = {
        "1. What time is it when the clock strikes 13? -> Time to get a new clock.",
        "2. How does a cucumber become a pickle? -> It goes through a jarring experience.",
        "3. What did one toilet say to the other? -> You look a bit flushed.",
        "4. What do you think of that new diner on the moon? -> Food was good, but there really wasn’t much atmosphere.",
        "5. Why did the dinosaur cross the road? -> Because the chicken wasn't born yet.",
        "6. What musical instrument is found in the bathroom? -> A tuba toothpaste."
        "7. Why can't Elsa from Frozen have a balloon? -> Because she will <let it go, let it go.>"
        "8. Why did the kid bring a ladder to school? -> Because she wanted to go to high school."
        "9. What do you call a dog magician? -> A labracadabrador."
    };

    // Calculate the number of messages in the array
    int num_messages = sizeof(messages) / sizeof(messages[0]);

    // Generate a random index between 0 and the number of messages
    srand(time(nullptr)); // Initialize the random number generator
    int index = rand() % num_messages;

    // Return the random message
    sendMessage_bot(messages[index], event);
}