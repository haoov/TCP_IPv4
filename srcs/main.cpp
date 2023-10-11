#include "../incs/PSocket.hpp"
#include "../incs/ASocket.hpp"

using namespace ft_irc;
using namespace std;

int main(int argc, char *argv[]) {
	if (argc < 1)
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
		ASocket *connexion = LstSocket.accept();
		std::string msg("Hello");
		connexion->send(msg);
		std::cout << "New connexion established" << std::endl;
		static_cast<void>(connexion);
	}
	catch (Error &e) {
		std::cout << e.what() << std::endl;
	}
}