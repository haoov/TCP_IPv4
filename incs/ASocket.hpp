/**
 * Class for active sockets using TCP on IPv4
*/

#ifndef ASOCKET_HPP
#define ASOCKET_HPP

#include "Socket.hpp"

namespace net {

	class ASocket : public Socket {
		public :
			/*------------------------------------*/
			/*     Constructors and destructor    */
			/*------------------------------------*/

			ASocket(int, sockaddr);
			ASocket(const ASocket &);
			~ASocket();
	
			/*------------------------------------*/
			/*              Operators             */
			/*------------------------------------*/

			ASocket &operator=(const ASocket &);

			/*------------------------------------*/
			/*               Methods              */
			/*------------------------------------*/

			//write the content of m_wrbuf on the socket
			int send();

			//read m_rdsize bits from the socket to m_rdbuf
			int receive(int = 0);
			std::string rdbuf() const throw();

		private :
			//reading buffer
			std::string m_rdbuf;

			//writing buffer
			std::string m_wrbuf;

			//max reading size
			static const size_t m_rdsize = 1024;
	};
}

#endif