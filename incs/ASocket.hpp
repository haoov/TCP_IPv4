/**
 * Class for active sockets using TCP on IPv4
 * Active sockets are used by clients who initiate 
 * the connexion for exchanging data.
*/

#ifndef ASOCKET_HPP
#define ASOCKET_HPP

#include "defines.hpp"
#include "Socket.hpp"
#include <errno.h>

namespace TCP_IPv4 {

	class ASocket : public Socket {
		public :
			/*------------------------------------*/
			/*     Constructors and destructor    */
			/*------------------------------------*/

			ASocket(int, sockaddr);
			ASocket(const ASocket &);
			~ASocket() _NOEXCEPT;
	
			/*------------------------------------*/
			/*              Operators             */
			/*------------------------------------*/

			ASocket &operator=(const ASocket &);

			/*------------------------------------*/
			/*               Methods              */
			/*------------------------------------*/

			//write the content of m_wrbuf on the socket
			bool send();

			//read m_rdsize bits from the socket to m_rdbuf
			bool receive(int = 0);

			//write the msg to m_wrbuf
			void write(std::string &) _NOEXCEPT;

			//return the content of m_rdbuf
			std::string rdbuf() const _NOEXCEPT;

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