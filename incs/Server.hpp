

#ifndef SERVER_HPP
#define SERVER_HPP

#include "defines.hpp"
#include "PSocket.hpp"
#include "ASocket.hpp"
#include "SocEvent.hpp"
#include "Connexion.hpp"
#include <vector>


typedef std::vector<TCP_IPv4::ASocket *> ASocVec;

namespace TCP_IPv4 {

	class Server {
		public :
			/*------------------------------------*/
			/*    Constructors and destructor     */
			/*------------------------------------*/

			Server(std::string);
			Server(const Server &);
			~Server();
	
			/*------------------------------------*/
			/*              Operators             */
			/*------------------------------------*/

			Server &operator=(const Server &);
	
			/*------------------------------------*/
			/*               Methods              */
			/*------------------------------------*/

			void start(const char *);
			void newConnexion();
			bool isrunning() const _NOEXCEPT;
			bool isup() const _NOEXCEPT;
			bool isdown() const _NOEXCEPT;

			//only for testing
			ASocVec activeSockets() const _NOEXCEPT {return m_activeSockets;}
			SocEvent &socEvent();
			PSocket &socket();

		protected :
			std::string m_name;
			int m_state;
			PSocket m_passiveSocket;
			ASocVec m_activeSockets;
			SocEvent m_socEvent;
	
		private :
			void setState(int) _NOEXCEPT;
	};
}

#endif