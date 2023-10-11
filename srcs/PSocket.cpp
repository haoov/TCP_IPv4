#include "../incs/PSocket.hpp"

using namespace ft_irc;

/*------------------------------------*/
/*    Constructors and destructors    */
/*------------------------------------*/

PSocket::PSocket() {
	if ((m_fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
		throw Error("socket error");
}

PSocket::PSocket(const PSocket &other) {
	*this = other;
}

PSocket::~PSocket() {}

/*------------------------------------*/
/*             Operators              */
/*------------------------------------*/

PSocket &PSocket::operator=(const PSocket &other) {
	m_fd = other.fd();
	return *this;
}

/*------------------------------------*/
/*               Methods              */
/*------------------------------------*/

void PSocket::bind(const sockaddr *addr) {
	if (::bind(m_fd, addr, sizeof(*addr)) == -1)
		throw Error("bind error");
	::memcpy(&m_addr, addr, sizeof(*addr));
}

void PSocket::listen() {
	if (::listen(m_fd, m_backlog) == -1)
		throw Error("listen error");
}

ASocket *PSocket::accept() const {
	int fd;
	sockaddr addr;
	socklen_t addrlen = sizeof(addr);
	if ((fd = ::accept(m_fd, &addr, &addrlen)) == -1)
		throw Error("accept error");
	ASocket *activeSocket = new ASocket(fd, addr);
	return activeSocket;
}