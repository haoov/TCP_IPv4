#include "TCP_IPv4"
#include <error.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	if (argc < 2)
		return -1;
	try {
		TCP_IPv4::PSocket lstSocket;
		struct addrinfo hint, *res;
		::memset(&hint, 0, sizeof(hint));
		hint.ai_family = AF_INET;
		hint.ai_socktype = SOCK_STREAM;
		hint.ai_protocol = IPPROTO_TCP;
		if (getaddrinfo(NULL, argv[1], &hint, &res) == -1)
			return (perror("Error: "), -1);
		lstSocket.bind(res->ai_addr);
		lstSocket.listen();
		TCP_IPv4::ASocket *tcpSocket = lstSocket.accept();
		std::string msg("Salut\n");
		tcpSocket->setWriteable();
		tcpSocket->write(msg);
		tcpSocket->send();
		while (1) {
			tcpSocket->setReadable();
			tcpSocket->receive();
			std::cout << tcpSocket->rdbuf();
		}
	}
	catch (IRC::Error &e) {
		std::cout << e.what() << ": " << e.cause() << std::endl;
	}
}