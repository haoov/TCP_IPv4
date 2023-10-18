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
	m_state = RUNNING;
	while (this->running()) {
		this->wait();
	}
}

void Server::wait() {
	m_epoll.wait();
	for (int i = 0; i < m_epoll.eventNb(); ++i) {
		if (m_epoll.eventAt(i).events & EPOLLIN)
			m_sockets[m_epoll.eventAt(i).data.fd]->setReadable();
		if (m_epoll.eventAt(i).events & EPOLLOUT)
			m_sockets[m_epoll.eventAt(i).data.fd]->setWriteable();
	}
}

void Server::addUser() {
	ASocket *tcpSocket = m_socket.accept();
	User newUser(tcpSocket);
	m_users[tcpSocket] = newUser;
	m_epoll.add(tcpSocket->fd(), EPOLLIN);
}

void Server::sendTo(User &user, std::string &msg) {
	user.socket()->send(msg);
}

void Server::receiveFrom(User &user) {
	user.socket()->receive();
}

bool Server::running() const throw() {
	return (m_state == RUNNING);
}