/**
 * Base class for sockets
 * Each port can have a single passive socket binded to it,
 * await­ing in­com­ing con­nec­tions, and mul­ti­ple active sockets,
 * each cor­re­spond­ing to an open con­nec­tion on the port.
*/

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "defines.hpp"
#include "Error.hpp"
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>

namespace TCP_IPv4 {

	class Socket {
		public :
			typedef enum type {NOTYPE,PASSIVE,ACTIVE} e_type;

			/*------------------------------------*/
			/*    Constructors and destructor     */
			/*------------------------------------*/

			Socket();
			Socket(const Socket &);
			virtual ~Socket() _NOEXCEPT = 0;

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
			void setReadable() _NOEXCEPT;

			//set socket as writeable
			void setWriteable() _NOEXCEPT;

			//close socket
			void close();

			//return the socket fd
			int	fd() const _NOEXCEPT;

			//return true if socket is readable
			bool isReadable() const _NOEXCEPT;

			//return true if socket is writeable
			bool isWriteable() const _NOEXCEPT;

		protected :
			int m_fd;

			//struct storing the address binded to the socket 
			sockaddr m_addr;

			bool m_readable;
			bool m_writeable;

		private :
			e_type m_type;			

		public :
			/*------------------------------------*/
			/*             Exceptions             */
			/*------------------------------------*/

			class Failure : public Error {
				public :
					Failure(std::string);
			};
	};
}

#endif