#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <errno.h>
#include <cstring>
#include <fcntl.h>
#include <netdb.h>
#include <unistd.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


int main(int argc, char *argv[]) {
	int soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct addrinfo hint, *res;
	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = IPPROTO_TCP;
	getaddrinfo(NULL, argv[1], &hint, &res);
	bind(soc, res->ai_addr, sizeof(*(res->ai_addr)));
	fcntl(soc, F_SETFL, O_NONBLOCK);
	setsockopt(soc, SOL_SOCKET, SO_REUSEADDR, NULL, 0);
	listen(soc, 5);
	int epfd = epoll_create(1);
	struct epoll_event ev, *events;
	ev.data.fd = soc;
	ev.events = EPOLLIN | EPOLLET;
	epoll_ctl(epfd, EPOLL_CTL_ADD, soc, &ev);
	while (1) {
		int evnb;
		evnb = epoll_wait(epfd, events, 10, -1);
		if (evnb == -1)
			return (perror("epoll_wait: "), -1);
		for (int i = 0; i < evnb; ++i) {
			int evsoc = events[i].data.fd;
			if (evsoc == soc) {
				struct sockaddr addr;
				socklen_t addrlen = sizeof(addr);
				int tmpsoc = accept(soc, &addr, &addrlen);
				std::cout << "new connection" << std::endl;
				ev.data.fd = tmpsoc;
				fcntl(tmpsoc, F_SETFL, O_NONBLOCK);
				epoll_ctl(epfd, EPOLL_CTL_ADD, tmpsoc, &ev);
			}
			else {
				while (1) {
					char *buf = (char *)calloc(1024, sizeof(char));
					int n;
					n = recv(evsoc, buf, 1024, 0);
					if (n == -1) {
						std::cout << "-1" << std::endl;
						if (errno != EAGAIN)
							return (perror("recv: "), -1);
						break;
					}
					std::cout << buf;
				}
			}
		}
	}
	return 0;
}