#include "../incs/ASocket.hpp"

using namespace ft_irc;

/*------------------------------------*/
/*    Constructors and destructor     */
/*------------------------------------*/

ASocket::ASocket(int fd, sockaddr addr) {
	m_fd = fd;
	::memcpy(&m_addr, &addr, sizeof(addr));
}

ASocket::ASocket(const ASocket &other) {
	*this = other;
}

ASocket::~ASocket() {}

/*------------------------------------*/
/*              Operators             */
/*------------------------------------*/

ASocket &ASocket::operator=(const ASocket &other) {
	m_fd = other.fd();
	::memcpy(&m_addr, &other.m_addr, sizeof(other.m_addr));
	return *this;
}

/*------------------------------------*/
/*               Methods              */
/*------------------------------------*/

int ASocket::send(std::string &msg) {
	int nb;
	if ((nb = ::send(m_fd, msg.c_str(), msg.size(), 0)) == -1)
		throw Error("send error");
	return nb;
}

int ASocket::receive(int flags) {
	int nb;
	char buf[m_rdsize + 1];
	m_rdbuf.clear();
	if ((nb = ::recv(m_fd, buf, m_rdsize, flags)) == -1) {
		throw Error("recv error");
	}
	buf[nb] = '\0';
	m_rdbuf += buf;
	return nb;
}

std::string ASocket::rdbuf() const throw() {
	return m_rdbuf;
}