#ifndef USER_HPP
#define USER_HPP

#include "ASocket.hpp"

namespace ft_irc {

	class User {
		public :
			User();
			User(ASocket *);
			User(const User &);
			~User();
	
			User &operator=(const User &);

			ASocket *socket() const throw();
		protected :
	
		private :
			ASocket *m_socket;
			std::string m_username;
			std::string m_nickname;
	};
}

#endif