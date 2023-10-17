#ifndef EPOLL_HPP
#define EPOLL_HPP

#include <sys/epoll.h>
#include "Socket.hpp"

namespace ft_irc {

	class Epoll {
		public :
			Epoll(int = 0);
			Epoll(const Epoll &);
			~Epoll();
	
			Epoll &operator=(const Epoll &);
	
			void add(int, int);
			void wait();

			int eventNb() const throw();
			struct epoll_event eventAt(int) const;
		protected :
	
		private :
			int m_fd;
			struct epoll_event m_event;
			struct epoll_event *m_events;
			static const int m_maxevents = 10;
			int m_eventNb;
	};
}

#endif