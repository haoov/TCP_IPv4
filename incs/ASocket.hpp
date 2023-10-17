/**
 * Class for active sockets using TCP on IPv4
*/

#ifndef ASOCKET_HPP
#define ASOCKET_HPP

#include "Socket.hpp"

namespace ft_irc {

	class ASocket : public Socket {
		public :
			ASocket(int, sockaddr);
			ASocket(const ASocket &);
			~ASocket();
	
			ASocket &operator=(const ASocket &);

			int send(std::string &);
			int receive(int = 0);

			std::string rdbuf() const throw();
		protected :
	
		private :
			std::string m_rdbuf;
			std::string m_wrbuf;
			static const size_t m_rdsize = 1024;
	};
}

#endif