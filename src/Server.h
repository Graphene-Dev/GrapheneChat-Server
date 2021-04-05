#ifndef SERVER_H
#define SERVER_H

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

class Server {
private:
	websocketpp::server<websocketpp::config::asio> server;
public:
	Server();

	void run();
};

#endif // SERVER_H
