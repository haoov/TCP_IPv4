#include "PSocket.hpp"
#include "Error.hpp"

/*------------------------------------*/
/*    Constructors and destructors    */
/*------------------------------------*/

TCP_IPv4::PSocket::PSocket() {
	if ((m_fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
		throw IRC::Error("socket");
}

TCP_IPv4::PSocket::PSocket(const TCP_IPv4::PSocket &other) {
	*this = other;
}

TCP_IPv4::PSocket::~PSocket() _NOEXCEPT {
	::close(m_fd);
}

/*------------------------------------*/
/*             Operators              */
/*------------------------------------*/

TCP_IPv4::PSocket &TCP_IPv4::PSocket::operator=(const PSocket &other) {
	m_fd = other.fd();
	::memcpy(&m_addr, &other.m_addr, sizeof(other.m_addr));
	return *this;
}

/*------------------------------------*/
/*               Methods              */
/*------------------------------------*/

void TCP_IPv4::PSocket::bind(const sockaddr *addr) {
	if (::bind(m_fd, addr, sizeof(*addr)) == -1)
		throw IRC::Error("bind");
	::memcpy(&m_addr, addr, sizeof(*addr));
}

void TCP_IPv4::PSocket::listen() {
	if (::listen(m_fd, m_backlog) == -1)
		throw IRC::Error("listen");
}

TCP_IPv4::ASocket *TCP_IPv4::PSocket::accept() const {
	int fd;
	sockaddr addr;
	socklen_t addrlen = sizeof(addr);
	if ((fd = ::accept(m_fd, &addr, &addrlen)) == -1)
		throw IRC::Error("accept");
	ASocket *activeSocket = new ASocket(fd, addr);
	return activeSocket;
}