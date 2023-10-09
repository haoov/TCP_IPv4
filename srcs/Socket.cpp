#include "../incs/Socket.hpp"

using namespace ft_irc;

/*------------------------------------*/
/*    Constructors and destructors    */
/*------------------------------------*/

Socket::Socket() : m_fd(-1) {}

Socket::Socket(const Socket &other) throw() {
	*this = other;
}

Socket::~Socket() {
	this->close();
}

/*------------------------------------*/
/*              Operators             */
/*------------------------------------*/

Socket &ft_irc::Socket::operator=(const Socket &other) throw() {
	m_fd = other.m_fd;
	return *this;
}

/*------------------------------------*/
/*              Methods               */
/*------------------------------------*/

void Socket::initListen() {
	m_fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_fd < 0)
		throw std::string("socket error");
}

void Socket::bind(const sockaddr *addr) {
	if (::bind(m_fd, addr, sizeof (*addr)) < 0)
		throw std::string("bind error");
	std::memcpy(&m_addr, addr, sizeof (*addr));
}

void Socket::listen(int backlog) {
	if (::listen(m_fd, backlog) < 0)
		throw std::string("listen error");
}

void Socket::close() {
	if (::close(m_fd) < 0)
		throw std::string("close error");
}

/*------------------------------------*/
/*              Getters               */
/*------------------------------------*/

int Socket::fd() const throw() {
	return (m_fd);
}