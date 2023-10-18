#include <errno.h>
#include <cstdio>
#include "PSocket.hpp"

using namespace net;
using namespace std;

int main(int argc, char *argv[]) {
	if (argc < 2)
		return -1;

	static_cast<void>(argv);
	try {
		
	}
	catch (Error &e) {
		::perror(e.what());
	}
	return 0;
}
