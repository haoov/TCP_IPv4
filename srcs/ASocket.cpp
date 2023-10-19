#include "ASocket.hpp"
#include "Error.hpp"

/*------------------------------------*/
/*    Constructors and destructor     */
/*------------------------------------*/

TCP_IPv4::ASocket::ASocket(int fd, sockaddr addr) {
	m_fd = fd;
	::memcpy(&m_addr, &addr, sizeof(addr));
}

TCP_IPv4::ASocket::ASocket(const ASocket &other) {
	*this = other;
}

TCP_IPv4::ASocket::~ASocket() _NOEXCEPT {
	::close(m_fd);
}

/*------------------------------------*/
/*              Operators             */
/*------------------------------------*/

TCP_IPv4::ASocket &TCP_IPv4::ASocket::operator=(const ASocket &other) {
	m_fd = other.fd();
	::memcpy(&m_addr, &other.m_addr, sizeof(other.m_addr));
	return *this;
}

/*------------------------------------*/
/*               Methods              */
/*------------------------------------*/

bool TCP_IPv4::ASocket::send() {
	int nb;
	if (this->isWriteable()) {
		if ((nb = ::send(m_fd, m_wrbuf.c_str(), m_wrbuf.size(), 0)) == -1) {
			if (errno == EAGAIN)
				return false;
			throw IRC::Error("send");
		}
		m_writeable = false;
	}
	m_wrbuf.clear();
	return true;
}

bool TCP_IPv4::ASocket::receive(int flags) {
	if (this->isReadable()) {
		int nb;
		char buf[m_rdsize + 1];
		if ((nb = ::recv(m_fd, buf, m_rdsize, flags)) == -1) {
			if (errno == EAGAIN)
				return false;
			throw IRC::Error("recv");
		}
		buf[nb] = '\0';
		m_rdbuf += buf;
	}
	return true;
}

void TCP_IPv4::ASocket::write(std::string &msg) _NOEXCEPT {
	m_wrbuf += msg;
}