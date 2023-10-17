#include "Socket.hpp"

using namespace ft_irc;

/*------------------------------------*/
/*    Constrcutors and destructor     */
/*------------------------------------*/

Socket::Socket() : m_fd(-1) {}

Socket::Socket(const Socket &other) {
	*this = other;
}

Socket::~Socket() {
	this->close();
}

/*------------------------------------*/
/*             Operators              */
/*------------------------------------*/

Socket &Socket::operator=(const Socket &other) {
	m_fd = other.m_fd;
	::memcpy(&m_addr, &other.m_addr, sizeof(other.m_addr));
	return *this;
}

/*------------------------------------*/
/*              Methods               */
/*------------------------------------*/

void Socket::close() {
	if (::close(m_fd) != 0)
		throw Error("close error");
}

int Socket::fd() const throw() {
	return (m_fd);
}

void Socket::setNonBlock() {
	if (fcntl(m_fd, O_NONBLOCK) == -1) {
		throw Error("fcntl error");
	}
}

/*------------------------------------*/
/*              Exception             */
/*------------------------------------*/

Error::Error(const char *msg) : m_msg(msg) {}

const char *Error::what() const throw() {
	return (m_msg);
}