#include "SocEvent.hpp"

/*------------------------------------*/
/*    Constructors and destructor     */
/*------------------------------------*/

TCP_IPv4::SocEvent::SocEvent() : m_eventNb(0) {
	if ((m_fd = ::epoll_create(1)) == -1)
		throw TCP_IPv4::Error("epoll_create");
}

TCP_IPv4::SocEvent::~SocEvent() {}

/*------------------------------------*/
/*               Methods              */
/*------------------------------------*/

void TCP_IPv4::SocEvent::add(PSocket *socket, int events) {
	struct epoll_event event;
	event.data.fd = socket->fd();
	event.events = events | EPOLLET;
	if (::epoll_ctl(m_fd, EPOLL_CTL_ADD, socket->fd(), &event) == -1)
		throw TCP_IPv4::Error("epoll_ctl");
	m_sockets[socket->fd()] = static_cast<Socket *>(socket);
}

void TCP_IPv4::SocEvent::add(ASocket *socket, int events) {
	struct epoll_event event;
	event.data.fd = socket->fd();
	event.events = events | EPOLLET;
	if (::epoll_ctl(m_fd, EPOLL_CTL_ADD, socket->fd(), &event) == -1)
		throw TCP_IPv4::Error("epoll_ctl");
	m_sockets[socket->fd()] = static_cast<Socket *>(socket);
}

void TCP_IPv4::SocEvent::wait() {
	if ((m_eventNb = ::epoll_wait(m_fd, m_events, m_maxEvents, -1)) == -1)
		throw TCP_IPv4::Error("epoll_wait");
	for (int i = 0; i < m_eventNb; ++i) {
		if (m_events[i].data.fd & EPOLLIN)
			m_sockets[m_events[i].data.fd]->setReadable();
		if (m_events[i].data.fd & EPOLLOUT)
			m_sockets[m_events[i].data.fd]->setWriteable();
	}
}