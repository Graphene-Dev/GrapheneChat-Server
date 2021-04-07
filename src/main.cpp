#include "Server.h"

int main(int argc, char const *argv[]) {
  Server* s = new Server();
  s->run();
  return 0;
}
