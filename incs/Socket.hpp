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

namespace net {

	class Socket {
		public :
			/*------------------------------------*/
			/*    Constructors and destructor     */
			/*------------------------------------*/

			Socket();
			Socket(const Socket &);
			virtual ~Socket() throw();

			/*------------------------------------*/
			/*              Operators             */
			/*------------------------------------*/
		
			Socket &operator=(const Socket &);

			/*------------------------------------*/
			/*               Methods              */
			/*------------------------------------*/

			//set socket in nonblock mode
			void setNonBlock();

			//set socket as readable
			void setReadable() throw();

			//set socket as writeable
			void setWriteable() throw();

			//close socket
			void close();

			//return the socket fd
			int	fd() const throw();

			//return true if socket is readable
			bool isReadable() const throw();

			//return true if socket is writeable
			bool isWriteable() const throw();

		protected :
			int m_fd;
			sockaddr m_addr;
			bool m_readable;
			bool m_writeable;
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