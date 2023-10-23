#include "TCP_IPv4"
#include <vector>

int main(int argc, char *argv[]) {
	if (argc < 2)
		return -1;
	TCP_IPv4::Server server("test");
	try {
		server.start(argv[1]);
		while (server.isup()) {
			server.socEvent().wait();
			if (server.socket().isReadable()) {
				server.newConnexion();
			}
			for (int i = 0; i < server.activeSockets().size(); ++i) {
				if (server.activeSockets().at(i)->isReadable()) {
					server.activeSockets().at(i)->receive();
				}
			}
		}
	}
	catch (TCP_IPv4::Error &e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}