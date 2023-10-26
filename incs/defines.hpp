#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <exception>

# ifndef _NOEXCEPT
# define _NOEXCEPT _GLIBCXX_NOTHROW
# endif //_NOEXCEPT

enum serverState {
	UP,
	RUNNING,
	DOWN
};

enum socketType {
	ACTIVE,
	PASSIVE
};

enum logMode {
	CREATE,
	STATE,
	CONNECTION,
	COMMAND
};

#endif //DEFINES_HPP