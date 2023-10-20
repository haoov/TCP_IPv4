#include "PSocket.hpp"
#include "Error.hpp"

/*------------------------------------*/
/*    Constructors and destructors    */
/*------------------------------------*/

TCP_IPv4::PSocket::PSocket() {
	if ((m_fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
		throw TCP_IPv4::Error("socket");
}

TCP_IPv4::PSocket::PSocket(const TCP_IPv4::PSocket &other) {
	*this = other;
}

TCP_IPv4::PSocket::~PSocket() _NOEXCEPT {
	this->close();
}

/*------------------------------------*/
/*             Operators              */
/*------------------------------------*/

TCP_IPv4::PSocket &TCP_IPv4::PSocket::operator=(const PSocket &other) {
	Socket::operator=(other);
	return *this;
}

/*------------------------------------*/
/*               Methods              */
/*------------------------------------*/

void TCP_IPv4::PSocket::bind(const sockaddr *addr) {
	if (::bind(m_fd, addr, sizeof(*addr)) == -1)
		throw TCP_IPv4::Error("bind");
	m_addr = *addr;
}

void TCP_IPv4::PSocket::listen() {
	if (::listen(m_fd, m_backlog) == -1)
		throw TCP_IPv4::Error("listen");
}

TCP_IPv4::ASocket *TCP_IPv4::PSocket::accept() {
	int fd;
	sockaddr addr;
	socklen_t addrlen = sizeof(addr);
	if ((fd = ::accept(m_fd, &addr, &addrlen)) == -1)
		throw TCP_IPv4::Error("accept");
	ASocket *activeSocket = new ASocket(fd, addr);
	m_readable = false;
	return activeSocket;
}