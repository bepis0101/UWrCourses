#include "downloader.h"

input check_data_validity(int argc, const char* argv[]) {
  if (argc != 5) {
    cerr << "Incorrect number of arguments\n";
    exit(1);
  }
  input i = {argv[1], atoi(argv[2]), argv[3], atoi(argv[4])};
  if (i.port <= 0 || i.total_size <= 0 || i.total_size > 10000000) {
    cerr << "Invalid port or size of file\n";
    exit(1);
  }
  return i;
}

int create_socket() {
  int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sockfd < 0) {
    cerr << "Socket creation failed\n";
    exit(1);
  }
  return sockfd;
}

sockaddr_in setup_server_address(const input& i) {
  sockaddr_in server_addr{};
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(i.port);
  if (inet_pton(AF_INET, i.server_ip, &server_addr.sin_addr) <= 0) {
    cerr << "Address conversion failed\n";
    exit(1);
  }
  return server_addr;
}

void send_request(int sockfd, const sockaddr_in& server_addr, int start, uint16_t chunk_size) {
  char send_buff[64];
  int send_length = snprintf(send_buff, sizeof(send_buff), "GET %d %hu\n", start, chunk_size);
  ssize_t sent = sendto(sockfd, send_buff, send_length, 0, (sockaddr*)&server_addr, sizeof(server_addr));
  if (sent < 0) {
    cerr << "Request send failed\n";
    exit(1);
  }
}

bool receive_chunk(int sockfd, int start, uint16_t chunk_size, char* data_buf) {
  char recv_buff[MAX_DATAGRAMS + 64];
  pollfd pfd{sockfd, POLLIN, 0};
  int poll_ret = poll(&pfd, 1, TIMEOUT_MS);
  if (poll_ret == 0) {
    return false;
  }
  if (poll_ret < 0) {
    cerr << "Polling failed\n";
    exit(1);
  }

  sockaddr_in recv_addr{};
  socklen_t recv_length = sizeof(recv_addr);
  ssize_t bytes_received = recvfrom(sockfd, recv_buff, sizeof(recv_buff), 0, (sockaddr*)&recv_addr, &recv_length);
  if (bytes_received < 0) {
    return false;
  }

  string header;
  istringstream stream(string(recv_buff, bytes_received));
  getline(stream, header);
  int res_start, res_length;
  if (sscanf(header.c_str(), "DATA %d %d\n", &res_start, &res_length) != 2) {
    return false;
  }
  if (res_start != start || res_length != chunk_size) {
    return false;
  }

  const char* data_start = recv_buff + header.length() + 1;
  int data_bytes = bytes_received - (data_start - recv_buff);
  if (data_bytes != chunk_size) {
    return false;
  }

  memcpy(data_buf, data_start, chunk_size);
  return true;
}

void download_file(const input& i, int sockfd, const sockaddr_in& server_addr) {
  ofstream output_file(i.filename, ios::binary);
  if (!output_file) {
    cerr << "Output file open failed or file doesn't exist\n";
    exit(1);
  }

  int downloaded_bytes = 0;
  char data_buf[MAX_DATAGRAMS];

  while (downloaded_bytes < i.total_size) {
    uint16_t chunk_size = min((int)MAX_DATAGRAMS, i.total_size - downloaded_bytes);
    int start = downloaded_bytes;

    send_request(sockfd, server_addr, start, chunk_size);
    if (!receive_chunk(sockfd, start, chunk_size, data_buf)) {
      continue;
    }

    output_file.write(data_buf, chunk_size);
    if (!output_file) {
      cerr << "Output write failed\n";
      exit(1);
    }

    downloaded_bytes += chunk_size;
    cerr << "Progress " << downloaded_bytes << "/" << i.total_size << " bytes\n";
  }

  output_file.close();
}
