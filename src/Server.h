#ifndef SERVER_H
#define SERVER_H

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <set>

#include "rapidjson/document.h"

#include "DBManager.h"

class Server {
private:
	websocketpp::server<websocketpp::config::asio> server;
	std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>> conns;

	void (*db_callback) (int type, rapidjson::Value& object);

	DBManager* db;

	void on_open(websocketpp::connection_hdl);
	void on_close(websocketpp::connection_hdl);

	void on_message(websocketpp::connection_hdl hdl, websocketpp::server<websocketpp::config::asio>::message_ptr msg);

	void sendAll(std::string);

public:
	Server(DBManager* db);

	void run();
	void set_db_callback(void (*db_callback) (int type, rapidjson::Value& object));
};

#endif // SERVER_H
