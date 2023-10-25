

#ifndef SERVER_HPP
#define SERVER_HPP

#include "defines.hpp"
#include "PSocket.hpp"
#include "ASocket.hpp"
#include "SocEvent.hpp"
#include <vector>

typedef std::vector<TCP_IPv4::ASocket *> vec_ASocket;

namespace TCP_IPv4 {

	class Server {
		public :
			/*------------------------------------*/
			/*    Constructors and destructor     */
			/*------------------------------------*/

			Server(std::string);
			Server(const Server &);
			virtual ~Server();
	
			/*------------------------------------*/
			/*              Operators             */
			/*------------------------------------*/

			Server &operator=(const Server &);
	
			/*------------------------------------*/
			/*               Methods              */
			/*------------------------------------*/

			/**
			 * @brief bind the server's passive socket to the given 
			 * corresponding port (using TCP protocol and IPv4 familly) 
			 * then calls listen and adds it to socEvent handler
			 * 
			 * @param port the port on wich the socket should bind and 
			 * so the port on wich the clients should connect
			 * @exception throws TCP_IPv4::Error exception if any 
			 * system call fails
			*/
			void start(const char *);

			virtual void run();

			//accept a new connection and add it to socEvent handler
			void newConnection();

			//return true if the server can accept a new connection
			bool pendingConnection() const _NOEXCEPT;

			//return true if the server is running
			bool isrunning() const _NOEXCEPT;

			//return true if the server is up
			bool isup() const _NOEXCEPT;
			
			//return true if the server is down
			bool isdown() const _NOEXCEPT;

		protected :
			std::string m_name;
			int m_state;
			PSocket m_pSocket;
			vec_ASocket m_aSockets;
			SocEvent m_socEvent;

			/**
			 * @brief set the server's current state to the givent value 
			 * (see defines.h) If in VERBOSE mode print the state 
			 * to standard output
			*/
			void setState(int) _NOEXCEPT;

		public :
			/*------------------------------------*/
			/*              Exception             */
			/*------------------------------------*/

			class Failure : public TCP_IPv4::Error {
				public :
					Failure(std::string);
			};
	};
}

#endif