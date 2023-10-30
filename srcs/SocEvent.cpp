#include "SocEvent.hpp"
#include "ASocket.hpp"

/*------------------------------------*/
/*    Constructors and destructor     */
/*------------------------------------*/

TCP_IPv4::SocEvent::SocEvent() : m_eventNb(0) {
	if ((m_fd = ::epoll_create(1)) == -1)
		throw TCP_IPv4::Error("epoll_create");
	m_events = new struct epoll_event;
}

TCP_IPv4::SocEvent::~SocEvent() {
	::close(m_fd);
	if (m_events != NULL)
		delete m_events;
	m_events = NULL;
}

/*------------------------------------*/
/*             Operators              */
/*------------------------------------*/

TCP_IPv4::SocEvent &TCP_IPv4::SocEvent::operator=(const SocEvent &other) {
	m_fd = other.m_fd;
	m_events = other.m_events;
	m_eventNb = other.m_eventNb;
	m_sockets = other.m_sockets;
	return *this;
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
	if ((m_eventNb = ::epoll_wait(m_fd, m_events, m_maxEvents, -1)) == -1) {
		if (errno != EINTR)
			throw TCP_IPv4::Error("epoll_wait");
	}
	for (int i = 0; i < m_eventNb; ++i) {
		int fd = m_events[i].data.fd;
		int events = m_events[i].events;
		if (events & EPOLLIN)
			m_sockets[fd]->m_evFlags |= EPOLLIN;
		if (events & EPOLLOUT)
			m_sockets[fd]->m_evFlags |= EPOLLOUT;
	}
}