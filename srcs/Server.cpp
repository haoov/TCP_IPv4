#include "Server.hpp"

/*------------------------------------*/
/*    Constructors and destructor     */
/*------------------------------------*/

TCP_IPv4::Server::Server() : m_state(DOWN) {}

TCP_IPv4::Server::Server(const Server &other) {
	*this = other;
}

TCP_IPv4::Server::~Server() {}

/*------------------------------------*/
/*             Operators              */
/*------------------------------------*/

TCP_IPv4::Server &TCP_IPv4::Server::operator=(const Server &other) {
	m_state = other.m_state;
	m_PSocket = other.m_PSocket;
	m_ASockets = other.m_ASockets;
	return *this;
}

/*------------------------------------*/
/*              Methods               */
/*------------------------------------*/

void TCP_IPv4::Server::start(std::string &port) {
	struct addrinfo hint, *res;
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(NULL, port.c_str(), &hint, &res) == -1)
		throw TCP_IPv4::Error("getaddrinfo");
	while (res != NULL) {
		try {
			m_PSocket.bind(res->ai_addr);
		}
		catch (TCP_IPv4::Error &e) {
			continue;
		}
	}
}

bool TCP_IPv4::Server::isrunning() const _NOEXCEPT {
	return (m_state == RUNNING);
}

bool TCP_IPv4::Server::isup() const _NOEXCEPT {
	return (m_state == UP);
}

bool TCP_IPv4::Server::isdown() const _NOEXCEPT {
	return (m_state == DOWN);
}