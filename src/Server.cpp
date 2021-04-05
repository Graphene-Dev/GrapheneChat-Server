#include "Server.h"

#include <iostream>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

void on_message(websocketpp::server<websocketpp::config::asio> *server, websocketpp::connection_hdl hdl, websocketpp::server<websocketpp::config::asio>::message_ptr msg) {
  std::cout << "on_message called with hdl: " << hdl.lock().get()
            << " and message: " << msg->get_payload()
            << std::endl;

  try {
      server->send(hdl, msg->get_payload(), msg->get_opcode());
  } catch (websocketpp::exception const & e) {
      std::cout << "Echo failed because: "
                << "(" << e.what() << ")" << std::endl;
  }
}

Server::Server() {

}

void Server::run() {
	server.set_message_handler(bind(&on_message,&server,::_1,::_2));
	server.set_access_channels(websocketpp::log::alevel::all);
	server.set_error_channels(websocketpp::log::elevel::all);
  server.clear_access_channels(websocketpp::log::alevel::frame_payload);

	server.init_asio();
	server.listen(8080);
	server.start_accept();

	server.run();
}
