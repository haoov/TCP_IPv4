#include "User.hpp"

using namespace ft_irc;

/*------------------------------------*/
/*    Constructors and destructors    */
/*------------------------------------*/

User::User() {}

User::User(ASocket *socket) : m_socket(socket), m_username(), m_nickname() {}

User::User(const User &other) :m_socket(other.socket()) {
	*this = other;
}

User::~User() {}

/*------------------------------------*/
/*             Operators              */
/*------------------------------------*/

User &User::operator=(const User &other) {
	m_socket = other.m_socket;
	m_username = other.m_username;
	m_nickname = other.m_nickname;
	return *this;
}

/*------------------------------------*/
/*              Methods               */
/*------------------------------------*/

ASocket *User::socket() const throw() {
	return m_socket;
}