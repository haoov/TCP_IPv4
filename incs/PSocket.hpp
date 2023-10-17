/**
 * Class for passive sockets using TCP on IPv4
 * passive sockets are bind to an address and
 * will wait for an incoming connection that
 * will create a new active socket
*/

#ifndef PSOCKET_HPP
#define PSOCKET_HPP

#include "Socket.hpp"
#include "ASocket.hpp"
#include <sys/types.h>
#include <netdb.h>
#include <cstring>

namespace ft_irc {
	
	class PSocket : public Socket {
		public :
			PSocket();
			PSocket(const PSocket &);
			~PSocket();
	
			PSocket &operator=(const PSocket &);

			void bind(const sockaddr *);
			void listen();
			ASocket *accept() const;
	
		protected :
	
		private :
			//Max length for the connexion queue
			static const int m_backlog = 5;
	};
}

#endif