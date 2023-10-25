#include "Server.hpp"

/*------------------------------------*/
/*    Constructors and destructor     */
/*------------------------------------*/

TCP_IPv4::Server::Server(std::string name) : m_name(name), m_state(DOWN) {
	#ifdef VERBOSE
	std::cout << "server " << m_name << " created" << std::endl;
	#endif
}

TCP_IPv4::Server::Server(const Server &other) {
	*this = other;
}

TCP_IPv4::Server::~Server() {
	for (size_t i = 0; i < m_aSockets.size(); ++i)
		delete m_aSockets[i];
}

/*------------------------------------*/
/*             Operators              */
/*------------------------------------*/

TCP_IPv4::Server &TCP_IPv4::Server::operator=(const Server &other) {
	m_state = other.m_state;
	m_pSocket = other.m_pSocket;
	return *this;
}

/*------------------------------------*/
/*              Methods               */
/*------------------------------------*/

void TCP_IPv4::Server::start(const char *port) {
	if (this->isdown()) {
		struct addrinfo hint, *res;
		::memset(&hint, 0, sizeof(hint));
		hint.ai_family = AF_INET;
		hint.ai_socktype = SOCK_STREAM;
		hint.ai_protocol = IPPROTO_TCP;
		if (getaddrinfo(NULL, port, &hint, &res) == -1)
			throw TCP_IPv4::Error("getaddrinfo");
		while (res != NULL) {
			try {
				m_pSocket.bind(res->ai_addr);
			}
			catch (TCP_IPv4::Error &e) {
				continue;
			}
			break;
		}
		m_pSocket.listen();
		m_socEvent.add(&m_pSocket, EPOLLIN);
		this->setState(UP);
	}
}

TCP_IPv4::ASocket *TCP_IPv4::Server::newConnection() {
	TCP_IPv4::ASocket *newASocket = m_pSocket.accept();
	#ifdef VERBOSE
	std::cout << "new connexion on socket " << newASocket->fd() << std::endl;
	#endif
	m_aSockets.insert(m_aSockets.end(), newASocket);
	m_socEvent.add(newASocket, EPOLLIN | EPOLLOUT | EPOLLHUP);
	return newASocket;
}

bool TCP_IPv4::Server::pendingConnection() const _NOEXCEPT {
	return m_pSocket.isReadable();
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

/*------------------------------------*/
/*           Private Methods          */
/*------------------------------------*/

void TCP_IPv4::Server::setState(int newState) _NOEXCEPT {
	m_state = newState;
	#ifdef VERBOSE
	std::cout << "server " << m_name;
	if (this->isup())
		std::cout << " is up";
	if (this->isdown())
		std::cout << " is down";
	if (this->isrunning())
		std::cout << " is running";
	std::cout << std::endl;
	#endif
}

/*------------------------------------*/
/*             Exception              */
/*------------------------------------*/

TCP_IPv4::Server::Failure::Failure(std::string what) : TCP_IPv4::Error(what) {}