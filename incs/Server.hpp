#ifndef SERVER_HPP
#define SERVER_HPP

#include "PSocket.hpp"
#include "ASocket.hpp"
#include "User.hpp"
#include "Epoll.hpp"
#include <map>

namespace ft_irc {

	class Server {
		public :
			typedef std::map<ASocket*, User> userMap;
			typedef std::map<int, Socket*> socketMap;
			typedef enum state {RUNNING,DOWN} e_state;
			
			Server(std::string);
			Server(const Server &);
			~Server();
	
			Server &operator=(const Server &);

			void run();
			void wait();
			void addUser();
			void sendTo(User &, std::string &);
			void receiveFrom(User &);
			bool running() const throw();
		protected :
	
		private :
			e_state m_state;
			PSocket m_socket;
			Epoll m_epoll;
			socketMap m_sockets;
			userMap m_users;
	};
}

#endif