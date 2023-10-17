#include "Server.hpp"

using namespace ft_irc;

/*------------------------------------*/
/*    Constructors and destructors    */
/*------------------------------------*/

Server::Server(std::string port) : m_socket(), m_epoll() {
	addrinfo hint, *res;
	::memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(NULL, port.c_str(), &hint, &res) == -1)
			throw Error("getaddrinfo error");
	m_socket.setNonBlock();
	m_socket.bind(res->ai_addr);
	m_socket.listen();
	m_epoll.add(m_socket.fd(), EPOLLIN);
}

Server::Server(const Server &other) : m_epoll() {
	*this = other;
}

Server::~Server() {}

/*------------------------------------*/
/*             Operators              */
/*------------------------------------*/

Server &Server::operator=(const Server &other) {
	static_cast<void>(other);
	return *this;
}

/*------------------------------------*/
/*              Methods               */
/*------------------------------------*/

void Server::run() {
	while (1) {
		m_epoll.wait();
		for (int i = 0; i < m_epoll.eventNb(); ++i) {
			if (m_epoll.eventAt(i).data.fd == m_socket.fd())
				this->addUser();
		}
	}
}

void Server::addUser() {
	ASocket *tcpSocket = m_socket.accept();
	m_users.insert(std::pair<ASocket *, User>(tcpSocket, User(*tcpSocket)));
	//m_users[tcpSocket] = User(*tcpSocket);
	m_epoll.add(tcpSocket->fd(), EPOLLIN);
}