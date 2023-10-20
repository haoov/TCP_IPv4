

#ifndef SERVER_HPP
#define SERVER_HPP

#include "defines.hpp"
#include "PSocket.hpp"
#include "ASocket.hpp"
#include "SocEvent.hpp"
#include <map>

namespace TCP_IPv4 {

	class Server {
		public :
			typedef std::map<int, ASocket *> socketMap;
			typedef enum state {UP,RUNNING,DOWN} e_state;

			/*------------------------------------*/
			/*    Constructors and destructor     */
			/*------------------------------------*/

			Server();
			Server(const Server &);
			~Server();
	
			/*------------------------------------*/
			/*              Operators             */
			/*------------------------------------*/

			Server &operator=(const Server &);
	
			/*------------------------------------*/
			/*               Methods              */
			/*------------------------------------*/

			void start(std::string &);
			bool isrunning() const _NOEXCEPT;
			bool isup() const _NOEXCEPT;
			bool isdown() const _NOEXCEPT;

		protected :
			e_state m_state;
			PSocket m_passiveSocket;
			socketMap m_activeSockets;
			SocEvent m_socEvent;
	
		private :
	};
}

#endif