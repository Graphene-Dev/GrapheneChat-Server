#include "Server.h"
#include "DBManager.h"

#include <thread>
#include <functional>

DBManager* db;

void db_cb(int type, rapidjson::Value& object) {
  switch (type) {
    case 1:
      db->addMessage(object);
      break;
  }
}

int main(int argc, char const *argv[]) {
  db = new DBManager();
  Server* s = new Server(db);
  s->set_db_callback(db_cb);
  std::thread server_thread(&Server::run, std::ref(s));

  server_thread.join();
  return 0;
}
