/**
 * Base class for sockets
 * Each port can have a single passive socket binded to it,
 * await­ing in­com­ing con­nec­tions, and mul­ti­ple active sockets,
 * each cor­re­spond­ing to an open con­nec­tion on the port.
*/

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>

namespace ft_irc {

	class Socket {
		public :
			Socket();
			Socket(const Socket &);
			virtual ~Socket();

			Socket &operator=(const Socket &);

			void setNonBlock();
			void close();
			int fd() const throw();
	
		protected :
			int m_fd;
			sockaddr m_addr;
	
		private :
	};

	class Error : public std::exception {
		public :
			Error(const char *);
			const char *what() const throw();
		private :
			const char *m_msg;
	};
}

#endif