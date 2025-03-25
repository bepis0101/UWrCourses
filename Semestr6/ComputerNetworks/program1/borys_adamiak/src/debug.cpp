// Borys Adamiak 337295
#include "debug.h"

void Debug::print_send_packet(const char* input_ip, int ttl) {
  std::cout << "Packet sent to " << input_ip << " with TTL = " << ttl << "\n";
}
void Debug::print_receive_packet(ssize_t received_bytes, sockaddr_in* sender) {
  if (received_bytes > 0) {
    std::cout << "Received packet from " << inet_ntoa(sender->sin_addr) << "\n";
  }  
}
