// Borys Adamiak 337295
#include "network.h"

int create_socket() {
  int sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
  return sock_fd;
}

void check_socket(int sock_fd) {
  if(sock_fd < 0) {
    std::cerr << "socket error\n";
    exit(0);
  }
  return;
}

void print_as_bytes(unsigned char* buff, ssize_t length)
{
  for (ssize_t i = 0; i < length; i++, buff++)
    printf("%.2x ", *buff);
}
