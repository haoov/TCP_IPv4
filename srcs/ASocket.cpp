#include "../incs/ASocket.hpp"

using namespace ft_irc;

/*------------------------------------*/
/*    Constructors and destructor     */
/*------------------------------------*/

ASocket::ASocket(int fd, sockaddr addr) {
	m_fd = fd;
	::memcpy(&m_addr, &addr, sizeof(addr));
}

ASocket::ASocket(const ASocket &other) {
	*this = other;
}

ASocket::~ASocket() {}

/*------------------------------------*/
/*              Operators             */
/*------------------------------------*/

ASocket &ASocket::operator=(const ASocket &other) {
	m_fd = other.fd();
	return *this;
}

/*------------------------------------*/
/*               Methods              */
/*------------------------------------*/

int ASocket::send(std::string &msg) {
	int nb;
	if ((nb = ::send(m_fd, msg.c_str(), msg.size(), 0)) == -1)
		throw Error("send error");
	return nb;
}