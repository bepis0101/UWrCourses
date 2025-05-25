#pragma once

#include <iostream>
#include <fstream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <poll.h>
#include <sstream>
#include <unistd.h>
#include <cstring>

using namespace std;

constexpr uint16_t MAX_DATAGRAMS = 1000;
constexpr uint16_t TIMEOUT_MS = 2000;

struct input {
  const char* server_ip;
  int port;
  const char* filename;
  int total_size;
};

input check_data_validity(int argc, const char* argv[]);
int create_socket();
sockaddr_in setup_server_address(const input& i);
void send_request(int sockfd, const sockaddr_in& server_addr, int start, uint16_t chunk_size);
bool receive_chunk(int sockfd, int start, uint16_t chunk_size, char* data_buf);
void download_file(const input& i, int sockfd, const sockaddr_in& server_addr);
