#include "Server.hpp"
#include <errno.h>
#include <cstdio>

using namespace ft_irc;
using namespace std;

int main(int argc, char *argv[]) {
	if (argc < 2)
		return -1;

	static_cast<void>(argv);
	try {
		std::string port(argv[1]);
		Server ircServer(port);
		ircServer.run();
	}
	catch (Error &e) {
		::perror(e.what());
	}
	return 0;
}
