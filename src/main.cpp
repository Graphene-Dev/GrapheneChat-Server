#include "Server.h"
#include "DBManager.h"

#include <thread>
#include <functional>

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

DBManager* db;
Server* s;

void db_cb(int type, rapidjson::Value& object, websocketpp::connection_hdl hdl) {
  switch (type) {
    case 1:
      db->addMessage(object);
      break;
    case 2:
      rapidjson::Document out = db->last50(0);
      rapidjson::StringBuffer buffer;
      rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
      out.Accept(writer);
      s->server.send(hdl, buffer.GetString(), websocketpp::frame::opcode::text);
      break;
  }
}

int main(int argc, char const *argv[]) {
  db = new DBManager();
  s = new Server(db);
  s->set_db_callback(db_cb);
  std::thread server_thread(&Server::run, std::ref(s));

  server_thread.join();
  return 0;
}
