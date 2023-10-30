#include "Server.hpp"

/*------------------------------------*/
/*    Constructors and destructor     */
/*------------------------------------*/

TCP_IPv4::Server::Server(std::string name) : m_name(name), m_state(DOWN) {
	m_logFile.exceptions(std::ios_base::failbit | std::ios_base::badbit);
	m_logFile.open("server.log", std::ios_base::out |std::ios_base::app);
	signal_handler(this);
	time_t rawTime = time(NULL);
	m_creationTime = ::asctime(::localtime(&rawTime));
	this->log() << "server " << m_name << " created" << std::endl;
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
	m_name = other.m_name;
	m_state = other.m_state;
	m_pSocket = other.m_pSocket;
	m_aSockets = other.m_aSockets;
	m_port = other.m_port;
	return *this;
}

/*------------------------------------*/
/*              Methods               */
/*------------------------------------*/

void TCP_IPv4::Server::start(const char *port) {
	if (this->isdown()) {
		m_port = port;
		struct addrinfo hint, *res;
		::memset(&hint, 0, sizeof(hint));
		hint.ai_family = AF_INET;
		hint.ai_socktype = SOCK_STREAM;
		hint.ai_protocol = IPPROTO_TCP;
		if (getaddrinfo(NULL, port, &hint, &res) == -1)
			throw TCP_IPv4::Error("getaddrinfo");
		for (; res != NULL; res = res->ai_next) {
			try {
				m_pSocket.bind(res->ai_addr);
			}
			catch (TCP_IPv4::Error &e) {
				continue;
			}
			break;
		}
		if (res == NULL)
			throw TCP_IPv4::Error("bind: no available address");
		m_pSocket.listen();
		m_socEvent.add(&m_pSocket, EPOLLIN);
		::freeaddrinfo(res);
		this->setState(UP);
	}
}

TCP_IPv4::ASocket *TCP_IPv4::Server::newConnection() {
	TCP_IPv4::ASocket *newASocket = m_pSocket.accept();
	newASocket->setNonBlock();
	m_aSockets.insert(m_aSockets.end(), newASocket);
	m_socEvent.add(newASocket, EPOLLIN | EPOLLOUT | EPOLLHUP);
	this->log()	<< "new connection to " << "[" << newASocket->host()
				<< ":" << newASocket->serv() << "]" << std::endl;
	return newASocket;
}

void TCP_IPv4::Server::connectionClosed(ASocket *socket) {
	std::vector<ASocket *>::iterator it;
	for (it = m_aSockets.begin(); it != m_aSockets.end(); ++it) {
		if (*it == socket) {
			delete *it;
			m_aSockets.erase(it);
			break;
		}
	}
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

std::ofstream &TCP_IPv4::Server::log() _NOEXCEPT {
	time_t rawTime;
	struct tm *localTime;
	::time(&rawTime);
	localTime = ::localtime(&rawTime);
	m_logFile	<< "[" << std::setfill('0') << std::setw(2) << localTime->tm_mday
				<< "-" << std::setfill('0') << std::setw(2) << localTime->tm_mon
				<< "-" << std::setfill('0') << std::setw(4) << localTime->tm_year
				<< " at "
				<< std::setfill('0') << std::setw(2) << localTime->tm_hour
				<< ":" << std::setfill('0') << std::setw(2) << localTime->tm_min
				<< ":" << std::setfill('0') << std::setw(2) << localTime->tm_sec
				<< "] ";
	return m_logFile;
}

/*------------------------------------*/
/*           Private Methods          */
/*------------------------------------*/

void TCP_IPv4::Server::setState(int newState) _NOEXCEPT {
	m_state = newState;
	switch (m_state)
	{
	case UP :
		this->log() << "server " << m_name << " up" << std::endl;
		break;
	case RUNNING :
		this->log() << "server " << m_name << " running" << std::endl;
		break;
	case DOWN :
		this->log() << "server " << m_name << " down" << std::endl;
	default:
		break;
	}
}