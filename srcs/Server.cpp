#include "Server.hpp"

/*------------------------------------*/
/*    Constructors and destructor     */
/*------------------------------------*/

TCP_IPv4::Server::Server(std::string name) : m_name(name), m_state(DOWN) {
	m_logFile.exceptions(std::ios_base::failbit | std::ios_base::badbit);
	m_logFile.open("server_log", std::ios_base::out |std::ios_base::trunc);
	m_logFile << "server " << m_name << " created" << std::endl << std::endl;
}

TCP_IPv4::Server::Server(const Server &other) {
	*this = other;
}

TCP_IPv4::Server::~Server() {
	for (size_t i = 0; i < m_aSockets.size(); ++i)
		delete m_aSockets[i];
	m_logFile.close();
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
	m_logFile << newASocket->host() << " connected on socket " << newASocket->fd() << std::endl << std::endl;
	newASocket->setNonBlock();
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
	m_logFile << "server " << m_name;
	if (this->isup())
		m_logFile << " is up";
	if (this->isdown())
		m_logFile << " is down";
	if (this->isrunning())
		m_logFile << " is running";
	m_logFile << std::endl << std::endl;
}

/*------------------------------------*/
/*             Exception              */
/*------------------------------------*/

TCP_IPv4::Server::Failure::Failure(std::string what) : TCP_IPv4::Error(what) {}

//for testing only
void TCP_IPv4::Server::runTest() {
	m_socEvent.wait();
	if (this->pendingConnection()) {
		TCP_IPv4::ASocket *newASocket = this->newConnection();
		newASocket->write("001 : Welcome\n");
		newASocket->write("375 :- Test\n");
		newASocket->write("372 :- Hello\n");
		newASocket->write("376 : End of /MOTD command\n");
		newASocket->send();
	}
	for (size_t i = 0; i < m_aSockets.size(); ++i) {
		if (!m_aSockets[i]->connected())
			m_logFile << m_aSockets[i]->host() << " closed the connection" << std::endl;
		if (m_aSockets[i]->isReadable()) {
			m_aSockets[i]->receive();
			if (!m_aSockets[i]->data().empty()) {
				m_logFile	<< "command received: " << std::endl
							<< m_aSockets[i]->data() << std::endl;
			}
		}
	}
}