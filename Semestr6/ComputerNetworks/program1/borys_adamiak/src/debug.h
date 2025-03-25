// Borys Adamiak 337295
#include "icmp.h"
class Debug {
  public:
  void print_send_packet(const char* input_ip, int ttl);
  void print_receive_packet(ssize_t received_bytes, sockaddr_in* sender);
};