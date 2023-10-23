#include "ASocket.hpp"
#include "Error.hpp"

/*------------------------------------*/
/*    Constructors and destructor     */
/*------------------------------------*/

TCP_IPv4::ASocket::ASocket() {}

TCP_IPv4::ASocket::ASocket(int fd, sockaddr addr) {
	m_fd = fd;
	m_addr = addr;
	m_type = ACTIVE;
	m_connexionState = UP;
	this->setNonBlock();
}

TCP_IPv4::ASocket::ASocket(const ASocket &other) {
	*this = other;
}

TCP_IPv4::ASocket::~ASocket() _NOEXCEPT {
	this->close();
}

/*------------------------------------*/
/*              Operators             */
/*------------------------------------*/

TCP_IPv4::ASocket &TCP_IPv4::ASocket::operator=(const ASocket &other) {
	Socket::operator=(other);
	m_rdbuf = other.m_rdbuf;
	m_wrbuf = other.m_wrbuf;
	return *this;
}

/*------------------------------------*/
/*               Methods              */
/*------------------------------------*/

int TCP_IPv4::ASocket::send() {
	int nb;
	if (!m_writeable)
		throw TCP_IPv4::Socket::Failure("socket is not writeable");
	if (m_connexionState == DOWN)
		throw TCP_IPv4::Socket::Failure("connexion is down");
	if ((nb = ::send(m_fd, m_wrbuf.c_str(), m_wrbuf.size(), 0)) == -1) {
		if (errno != EAGAIN)
			throw TCP_IPv4::Error("send");
	}
	m_writeable = false;
	m_wrbuf.clear();
	return nb;
}

int TCP_IPv4::ASocket::receive(int flags) {
	if (!m_readable)
		throw TCP_IPv4::Socket::Failure("socket is not readable");
	if (m_connexionState == DOWN)
		throw TCP_IPv4::Socket::Failure("connexion is down");
	int nb;
	int ret = 0;
	char buf[m_rdsize + 1];
	do {
		nb = ::recv(m_fd, buf, m_rdsize, flags);
		if (nb == -1) {
			if (errno != EAGAIN)
				throw TCP_IPv4::Error("recv");
		}
		else {
			buf[nb] = '\0';
			m_rdbuf += buf;
			ret += nb;
		}
	} while (nb > 0);
	m_readable = false;
	return ret;
}

void TCP_IPv4::ASocket::write(std::string &msg) _NOEXCEPT {
	m_wrbuf += msg;
}

int TCP_IPv4::ASocket::connexionState() const _NOEXCEPT {
	return m_connexionState;
}

//for testing only
std::string TCP_IPv4::ASocket::rdbuf() const _NOEXCEPT {
	return m_rdbuf;
}