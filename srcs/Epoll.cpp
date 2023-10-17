#include "Epoll.hpp"

using namespace ft_irc;

/*------------------------------------*/
/*    Constructors and destructor     */
/*------------------------------------*/

Epoll::Epoll(int nb) {
	if ((m_fd = ::epoll_create(nb)) == -1) {
		throw Error("epoll_create error");
	}
}

Epoll::Epoll(const Epoll &other) {
	*this = other;
}

Epoll::~Epoll() {
	if (::close(m_fd) == -1)
		throw Error("close error");
}

/*------------------------------------*/
/*             Operators              */
/*------------------------------------*/

Epoll &Epoll::operator=(const Epoll &other) {
	static_cast<void>(other);
	return *this;
}

/*------------------------------------*/
/*              Methods               */
/*------------------------------------*/

void Epoll::add(int socketfd, int events) {
	m_event.data.fd = socketfd;
	m_event.events = events | EPOLLET;
	if (::epoll_ctl(m_fd, EPOLL_CTL_ADD, socketfd, &m_event) == -1)
		throw Error("epoll_ctl error");
}

void Epoll::wait() {
	if ((m_eventNb = ::epoll_wait(m_fd, m_events, m_maxevents, -1)) == -1)
		throw Error("epoll_wait error");
}

int Epoll::eventNb() const throw() {
	return m_eventNb;
}

struct epoll_event Epoll::eventAt(int i) const {
	if (i < 0 || i > m_eventNb)
		throw Error("epoll out of range");
	return m_events[i];
}