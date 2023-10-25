#include "ASocket.hpp"
#include "Error.hpp"

/*------------------------------------*/
/*    Constructors and destructor     */
/*------------------------------------*/

TCP_IPv4::ASocket::ASocket() {}

TCP_IPv4::ASocket::ASocket(int fd, sockaddr addr) : TCP_IPv4::Socket() {
	m_fd = fd;
	m_addr = addr;
	m_type = ACTIVE;
	m_evFlags |= EPOLLIN | EPOLLOUT;
	char host[NI_MAXHOST];
	char serv[NI_MAXSERV];
	if (::getnameinfo(&m_addr, sizeof(m_addr), host, sizeof(host), serv, sizeof(serv), NI_NAMEREQD) == -1)
		throw TCP_IPv4::Error("getnameinfo");
	m_host = host;
	m_serv = serv;
}

TCP_IPv4::ASocket::ASocket(const ASocket &other) : TCP_IPv4::Socket() {
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
	if (!this->isWriteable())
		throw TCP_IPv4::Socket::Failure("socket is not writeable");
	if (m_evFlags & EPOLLHUP)
		throw TCP_IPv4::Socket::Failure("connexion is down");
	if ((nb = ::send(m_fd, m_wrbuf.c_str(), m_wrbuf.size(), 0)) == -1) {
		if (errno != EAGAIN)
			throw TCP_IPv4::Error("send");
	}
	m_evFlags &= ~EPOLLOUT;
	m_wrbuf.clear();
	return nb;
}

int TCP_IPv4::ASocket::receive(int flags) {
	if (!this->isReadable())
		throw TCP_IPv4::Socket::Failure("socket is not readable");
	if (m_evFlags & EPOLLHUP)
		throw TCP_IPv4::Socket::Failure("connexion is down");
	m_rdbuf.clear();
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
	m_evFlags &= ~EPOLLIN;
	return ret;
}

void TCP_IPv4::ASocket::write(std::string &msg) _NOEXCEPT {
	m_wrbuf += msg;
}

bool TCP_IPv4::ASocket::connected() const _NOEXCEPT {
	return (!(m_evFlags & EPOLLHUP));
}

const std::string &TCP_IPv4::ASocket::data() const _NOEXCEPT {
	return m_rdbuf;
}

const std::string &TCP_IPv4::ASocket::host() const _NOEXCEPT {
	return m_host;
}

const std::string &TCP_IPv4::ASocket::serv() const _NOEXCEPT {
	return m_serv;
}