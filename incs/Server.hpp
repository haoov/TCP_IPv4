#ifndef SERVER_HPP
#define SERVER_HPP

#include "PSocket.hpp"
#include "ASocket.hpp"
#include "User.hpp"
#include "Epoll.hpp"
#include <map>

namespace ft_irc {

typedef std::map<ASocket*, User> userMap;

	class Server {
		public :
			Server(std::string);
			Server(const Server &);
			~Server();
	
			Server &operator=(const Server &);

			void run();
			void addUser();
		protected :
	
		private :
			PSocket m_socket;
			Epoll m_epoll;
			userMap m_users;
	};
}

#endif