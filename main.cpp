#include "TCP_IPv4"
#include <vector>

int main(int argc, char *argv[]) {
	if (argc < 2)
		return -1;
	try {
		TCP_IPv4::Server ircServer("test");
		ircServer.start(argv[1]);
		std::vector<TCP_IPv4::ASocket *> actSockets;
		while (ircServer.isup()) {
			ircServer.socEvent().wait();
			if (ircServer.socket().isReadable()) {
				TCP_IPv4::ASocket *actSocket;
				actSocket = ircServer.socket().accept();
				actSockets.insert(actSockets.end(), actSocket);
				actSocket->setWriteable();
				std::string msg("hello\n");
				actSocket->write(msg);
				actSocket->send();
				ircServer.socEvent().add(actSocket, EPOLLIN);
			}
			else {
				std::vector<TCP_IPv4::ASocket *>::iterator it = actSockets.begin();
				for (; it != actSockets.end(); ++it) {
					if ((*it)->isReadable()) {
						(*it)->receive();
						std::cout << (*it)->rdbuf();
					}
				}
			}
		}
	}
	catch (TCP_IPv4::Error &e) {
		std::cout << e.what() << std::endl;
		return -1;
	}
	return 0;
}