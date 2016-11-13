#pragma once

#include <string>
#include "../utils/log.hpp"
#include "../utils/platform.hpp"

#if defined(JN_OS_WIN)

#include <windows.h>  
#define CLOSE_SOCKET(x)     ::closesocket(x)
#define ISSOCKHANDLE(x)     (x!=INVALID_SOCKET)  
#define BLOCKREADWRITE      0  
#define NONBLOCKREADWRITE   0  
#define SENDNOSIGNAL        0  
#define ETRYAGAIN(x)        (x==WSAEWOULDBLOCK||x==WSAETIMEDOUT)  
#define gxsprintf           sprintf_s  

#else

#include <stdlib.h>  
#include <errno.h>  
#include <unistd.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#define CLOSE_SOCKET(x)     ::close(x)
#define ISSOCKHANDLE(x)     (x>0)  
#define BLOCKREADWRITE      MSG_WAITALL  
#define NONBLOCKREADWRITE   MSG_DONTWAIT  
#define SENDNOSIGNAL        MSG_NOSIGNAL  
#define ETRYAGAIN(x)        (x==EAGAIN||x==EWOULDBLOCK)  
#define gxsprintf           snprintf  

#endif

namespace jian {

	class Socket {
	public:

#if defined(JN_OS_WIN)
		using ip_t = u_long;
		using port_t = u_short;
		using socket_t = SOCKET;
		using socklen_t = int;
#else
		using ip_t = int;
		using port_t = int;
		using socket_t = int;
		using socklen_t = ::socklen_t;
#endif
		struct accept_t {
			socket_t socket;
			std::string ip;
			int port;
		};

		Socket() {
#if defined(JN_OS_WIN)
			WSADATA data;
			if (WSAStartup(MAKEWORD(2, 2), &data) != 0) {
				throw "Socket::Socket() error!";
			}
#endif
		}

		~Socket() {
#if defined(JN_OS_WIN)
			WSACleanup();
#endif
		}

		socket_t open(int tcpudp) {
			int protocol = 0;
			socket_t s;

#if defined(JN_OS_WIN)
			if (tcpudp == SOCK_STREAM) protocol = IPPROTO_TCP;
			else if (tcpudp == SOCK_DGRAM) protocol = IPPROTO_UDP;
#endif
			s = socket(AF_INET, tcpudp, protocol);
			if (s == INVALID_SOCKET) throw "Create socket failed !";
			return s;
		}

		void close(socket_t &socket) {
			if (ISSOCKHANDLE(socket)) {
				CLOSE_SOCKET(socket);
				socket = INVALID_SOCKET;
			}
		}

		void set_sin(sockaddr_in &sin, ip_t ip, port_t port) {
			sin.sin_family = AF_INET;
			sin.sin_addr.s_addr = ip;
			sin.sin_port = htons(port);
			std::memset(sin.sin_zero, 0x00, 8);
		}

		int bind_local(socket_t socket, port_t port) {
			sockaddr_in sin;
			set_sin(sin, htonl(INADDR_ANY), port);
			return ::bind(socket, (struct sockaddr *)&sin, sizeof(sockaddr_in));
			//if (ret == SOCKET_ERROR)  throw "Socket::bind_local failed!";
		}

		int bind(socket_t socket, std::string ip, port_t port) {
			sockaddr_in sin;
			set_sin(sin, inet_addr(ip.c_str()), port);
			return ::bind(socket, (struct sockaddr *)&sin, sizeof(sockaddr_in));
			//if (ret == SOCKET_ERROR)  throw "Socket::bind failed!";
		}

		int connect(socket_t socket, std::string ip, port_t port) {
			sockaddr_in sin;
			set_sin(sin, inet_addr(ip.c_str()), port);
			return ::connect(socket, (struct sockaddr *)&sin, sizeof(sockaddr_in));
			//if (ret == SOCKET_ERROR)  throw "Socket::connect failed!";
		}

		int listen(socket_t socket, int max = 10) {
			return ::listen(socket, max);
			//if (ret == SOCKET_ERROR)  throw "Socket::listen failed!";
		}

		accept_t accept(socket_t socket) {
			sockaddr_in addr;
			accept_t rt;
			socklen_t l = sizeof(sockaddr_in);

			rt.socket = ::accept(socket, (struct sockaddr *)&addr, &l);
			rt.ip = inet_ntoa(addr.sin_addr);
			rt.port = addr.sin_port;
			return rt;
		}

		int send(socket_t socket, std::string content) {
			return ::send(socket, content.c_str(), content.size(), BLOCKREADWRITE | SENDNOSIGNAL);
			//if (ret == SOCKET_ERROR) throw "Socket::send failed!";
		}

		std::string recv(socket_t socket) {
			char buf[MAX_PATH];
			int ret = ::recv(socket, buf, MAX_PATH, BLOCKREADWRITE);
			if (ret == SOCKET_ERROR || ret == 0) throw "Socket::recv failed!";
			return std::string(buf, ret);
		}

		std::string recv_all(socket_t socket) {
			std::ostringstream stream;
			while (true) {
				try {
					stream << recv(socket);
				}
				catch (...) {
					break;
				}
			}
			return stream.str();
		}
	};
}