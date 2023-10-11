#include "../incs/Socket.hpp"

using namespace ft_irc;

/*------------------------------------*/
/*    Constrcutors and destructor     */
/*------------------------------------*/

Socket::Socket() : m_fd(-1) {}

Socket::~Socket() {
	this->close();
}

/*------------------------------------*/
/*              Methods               */
/*------------------------------------*/

void Socket::close() {
	if (::close(m_fd) != 0)
		throw Error("close error");
}

int Socket::fd() const throw() {
	return (m_fd);
}

/*------------------------------------*/
/*              Exception             */
/*------------------------------------*/

Error::Error(const char *msg) : m_msg(msg) {}

const char *Error::what() const throw() {
	return (m_msg);
}