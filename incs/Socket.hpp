/**
 * Encapsulating Sockets for TCP protocol on IPv4 address.
 * this class should handle creating socket and basic functions
*/

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <iostream>
#include <unistd.h>
#include <cstring>

namespace ft_irc {

	class Socket {
		public :
			Socket();
			Socket(const Socket &) throw();
			~Socket() throw();

			Socket &operator=(const Socket &) throw();

			void initListen();
			void bind(const sockaddr *);
			void listen(int);
			void close();

			int fd() const throw();

		protected :

		private :
			int m_fd;
			sockaddr m_addr;
	};

}

#endif //SOCKET_HPP