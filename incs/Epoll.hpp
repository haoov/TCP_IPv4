#ifndef EPOLL_HPP
#define EPOLL_HPP

#include "defines.hpp"
#include "Socket.hpp"
#include "PSocket.hpp"
#include "ASocket.hpp"
#include "Error.hpp"
#include <sys/epoll.h>
#include <map>

namespace TCP_IPv4 {

	class Epoll {
		public :
			typedef std::map<int, Socket *> socketMap;

			/*------------------------------------*/
			/*    Constructors and destructor     */
			/*------------------------------------*/

			Epoll();
			~Epoll();

			/*------------------------------------*/
			/*               Methods              */
			/*------------------------------------*/

			//add a passive socket to the poll
			void add(PSocket *, int);

			//add an active socket to the poll
			void add(ASocket *, int);

			//wait for event to occur an modify the corresponding sockets
			void wait();

		private :
			int m_fd;

			//a map of every sockets currently in the poll
			socketMap m_sockets;

			//array of struct representing events that occured after a call to wait
			struct epoll_event *m_events;

			int m_eventNb;
			static const int m_maxEvents = 10;
	};
}

#endif