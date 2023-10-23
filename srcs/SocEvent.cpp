#include "SocEvent.hpp"
#include "ASocket.hpp"

/*------------------------------------*/
/*    Constructors and destructor     */
/*------------------------------------*/

TCP_IPv4::SocEvent::SocEvent() : m_eventNb(0) {
	if ((m_fd = ::epoll_create(1)) == -1)
		throw TCP_IPv4::Error("epoll_create");
}

TCP_IPv4::SocEvent::~SocEvent() {
	if (::close(m_fd) == -1)
		throw TCP_IPv4::Error("epoll close");
}

/*------------------------------------*/
/*               Methods              */
/*------------------------------------*/

void TCP_IPv4::SocEvent::add(Socket *socket, int events) {
	struct epoll_event event;
	event.data.fd = socket->fd();
	event.events = events | EPOLLET;
	if (::epoll_ctl(m_fd, EPOLL_CTL_ADD, socket->fd(), &event) == -1)
		throw TCP_IPv4::Error("epoll_ctl");
	m_sockets[socket->fd()] = socket;
}

void TCP_IPv4::SocEvent::wait() {
	if ((m_eventNb = ::epoll_wait(m_fd, m_events, m_maxEvents, -1)) == -1)
		throw TCP_IPv4::Error("epoll_wait");
	for (int i = 0; i < m_eventNb; ++i) {
		int fd = m_events[i].data.fd;
		int events = m_events[i].events;
		if (events & EPOLLIN) {
			m_sockets[fd]->m_readable = true;
			#ifdef VERBOSE
			std::cout << "socketfd " << fd << " is now readable" << std::endl;
			#endif
		}
		if (events & EPOLLOUT)
			m_sockets[fd]->m_writeable = true;
		if (events & EPOLLHUP && m_sockets[fd]->m_type == ACTIVE)
			static_cast<ASocket *>(m_sockets[fd])->m_connexionState = DOWN;
	}
}