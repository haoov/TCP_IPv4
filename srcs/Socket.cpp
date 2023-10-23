#include "Socket.hpp"
#include "Error.hpp"

/*------------------------------------*/
/*    Constrcutors and destructor     */
/*------------------------------------*/

TCP_IPv4::Socket::Socket() : m_fd(-1), m_readable(false), m_writeable(false), m_type(ACTIVE) {}

TCP_IPv4::Socket::Socket(const Socket &other) {
	*this = other;
}

TCP_IPv4::Socket::~Socket() _NOEXCEPT {}

/*------------------------------------*/
/*             Operators              */
/*------------------------------------*/

TCP_IPv4::Socket &TCP_IPv4::Socket::operator=(const Socket &other) {
	m_fd = other.m_fd;
	m_type = other.m_type;
	m_addr = other.m_addr;
	m_readable = other.m_readable;
	m_writeable = other.m_writeable;
	return *this;
}

/*------------------------------------*/
/*              Methods               */
/*------------------------------------*/

void TCP_IPv4::Socket::close() {
	if (::close(m_fd) != 0)
		throw TCP_IPv4::Error("close");
}

int TCP_IPv4::Socket::fd() const _NOEXCEPT {
	return (m_fd);
}

void TCP_IPv4::Socket::setNonBlock() {
	if ((m_flags = fcntl(m_fd, F_GETFL)) == -1)
		throw TCP_IPv4::Error("fcntl");
	m_flags |= O_NONBLOCK;
	if (fcntl(m_fd, F_SETFL, m_flags) == -1)
		throw TCP_IPv4::Error("fcntl");
}

bool TCP_IPv4::Socket::isReadable() const _NOEXCEPT {
	return m_readable;
}

bool TCP_IPv4::Socket::isWriteable() const _NOEXCEPT {
	return m_writeable;
}

/*------------------------------------*/
/*             Exceptions             */
/*------------------------------------*/

TCP_IPv4::Socket::Failure::Failure(std::string what) : TCP_IPv4::Error(what) {}