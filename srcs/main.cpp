#include "../incs/PSocket.hpp"
#include "../incs/ASocket.hpp"
#include <sys/select.h>
#include <fcntl.h>

using namespace ft_irc;
using namespace std;

int main(int argc, char *argv[]) {
	if (argc < 2)
		return -1;

	static_cast<void>(argv);
	try {
		PSocket LstSocket;
		addrinfo hint, *res;
		::memset(&hint, 0, sizeof(hint));
		hint.ai_family = AF_INET;
		hint.ai_socktype = SOCK_STREAM;
		hint.ai_protocol = IPPROTO_TCP;
		if (getaddrinfo(NULL, argv[1], &hint, &res) == -1)
			return -1;
		LstSocket.bind(res->ai_addr);
		LstSocket.listen();
		setsockopt(LstSocket.fd(), SOL_SOCKET, SO_REUSEADDR, 0, sizeof(int));
		fcntl(LstSocket.fd(), O_NONBLOCK);
		ASocket *TcpSocket = LstSocket.accept();
		string msg("Welcome to my ft_irc project\n");
		TcpSocket->send(msg);
		while (1) {
		}
	}
	catch (Error &e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
