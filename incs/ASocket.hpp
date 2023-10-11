/**
 * Class for active sockets using TCP on IPv4
*/

#ifndef ASOCKET_HPP
#define ASOCKET_HPP

#include "Socket.hpp"
#include <cstring>

namespace ft_irc {

	class ASocket : public Socket {
		public :
			ASocket(int, sockaddr);
			ASocket(const ASocket &);
			~ASocket();
	
			ASocket &operator=(const ASocket &);

			int send(std::string &);
	
		protected :
	
		private :
	};
}

#endif