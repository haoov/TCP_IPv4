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

TCP_IPv4::Server::~Server() {}

/*------------------------------------*/
/*             Operators              */
/*------------------------------------*/

TCP_IPv4::Server &TCP_IPv4::Server::operator=(const Server &other) {
	m_state = other.m_state;
	m_passiveSocket = other.m_passiveSocket;
	m_activeSockets = other.m_activeSockets;
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
				m_passiveSocket.bind(res->ai_addr);
			}
			catch (TCP_IPv4::Error &e) {
				continue;
			}
			break;
		}
		m_passiveSocket.listen();
		m_socEvent.add(&m_passiveSocket, EPOLLIN);
		this->setState(UP);
	}
}

void TCP_IPv4::Server::newConnexion() {
	ASocket *newActiveSocket = m_passiveSocket.accept();
	m_activeSockets.insert(m_activeSockets.end(), newActiveSocket);
	m_socEvent.add(newActiveSocket, EPOLLIN);
	#ifdef VERBOSE
	std::cout << "new connexion on socket " << newActiveSocket->fd() << std::endl;
	#endif
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

//only for testing

TCP_IPv4::SocEvent &TCP_IPv4::Server::socEvent() {
	return m_socEvent;
}

TCP_IPv4::PSocket &TCP_IPv4::Server::socket() {
	return m_passiveSocket;
}