#include "Server.h"

#include <iostream>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

Server::Server() {

}

void Server::run() {
	server.set_message_handler(bind(&Server::on_message, this, ::_1,::_2));
	server.set_access_channels(websocketpp::log::alevel::all);
	server.set_error_channels(websocketpp::log::elevel::all);
  server.clear_access_channels(websocketpp::log::alevel::frame_payload);
  server.set_open_handler(bind(&Server::on_open, this, ::_1));
  server.set_close_handler(bind(&Server::on_close, this, ::_1));

	server.init_asio();
	server.listen(8080);
	server.start_accept();

	server.run();
}

void Server::on_message(websocketpp::connection_hdl hdl, websocketpp::server<websocketpp::config::asio>::message_ptr msg) {
  for (auto i : conns) {
    try {
      server.send(i, msg->get_payload(), websocketpp::frame::opcode::text);
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
