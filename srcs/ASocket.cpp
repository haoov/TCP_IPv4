#include "../incs/ASocket.hpp"

using namespace net;

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

int ASocket::send() {
	int nb = 0;
	if (this->isWriteable()) {
		if ((nb = ::send(m_fd, m_wrbuf.c_str(), m_wrbuf.size(), 0)) == -1) {
			if (errno == EAGAIN)
				return nb;
			throw Error("send error");
		}
		m_writeable = false;
	}
	m_wrbuf.clear();
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