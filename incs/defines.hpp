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

#define ERR_CONDOWN			"connexion is down"
#define ERR_NOTWRITEABLE	"socket is not writeable"
#define ERR_NOTREADABLE		"socket is not readable"

#endif //DEFINES_HPP