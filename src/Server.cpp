#include "Server.h"

#include <iostream>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include "rapidjson/document.h"

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

Server::Server(DBManager* db) {
	this->db = db;
}

void Server::set_db_callback(void (*db_callback) (int type, rapidjson::Value& object, websocketpp::connection_hdl hdl)) {
	this->db_callback = db_callback;
}

void Server::run() {
	server.set_message_handler(bind(&Server::on_message, this, ::_1,::_2));
	server.set_access_channels(websocketpp::log::alevel::none);
	server.set_error_channels(websocketpp::log::elevel::info);
  server.clear_access_channels(websocketpp::log::alevel::frame_payload);
  server.set_open_handler(bind(&Server::on_open, this, ::_1));
  server.set_close_handler(bind(&Server::on_close, this, ::_1));
	server.set_reuse_addr(true);

	server.init_asio();
	server.listen(8080);
	server.start_accept();

	server.run();
}

void Server::on_message(websocketpp::connection_hdl hdl, websocketpp::server<websocketpp::config::asio>::message_ptr msg) {
	rapidjson::Document document;
	document.Parse(msg->get_payload().c_str());
	if (document["type"] == "NEW_MESSAGE") {
		db_callback(1, document["data"], hdl);
		sendAll(msg->get_payload());
	}else if (document["type"] == "LAST_50") {
		db_callback(2, document["data"], hdl);
	}
}

void Server::sendAll(std::string msg) {
  for (auto i : conns) {
    try {
      server.send(i, msg, websocketpp::frame::opcode::text);
    } catch (websocketpp::exception const & e) {
      std::cout << "Echo failed because: "
      << "(" << e.what() << ")" << std::endl;
    }
  }
}

void Server::on_open(websocketpp::connection_hdl hdl) {
  conns.insert(hdl);
}

void Server::on_close(websocketpp::connection_hdl hdl) {
  conns.erase(hdl);
}
