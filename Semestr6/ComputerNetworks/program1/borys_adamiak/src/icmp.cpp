// Borys Adamiak 337295
#include "icmp.h"

void create_echo_packet(icmp* header, uint16_t ttl, uint16_t seq) {
  header->icmp_type = ICMP_ECHO;
  header->icmp_cksum = 0;
  header->icmp_code = 0;
  header->icmp_hun.ih_idseq.icd_id = getpid();
  header->icmp_hun.ih_idseq.icd_seq = ((ttl-1)*3+seq);
  header->icmp_cksum = compute_icmp_checksum(header, sizeof(*header));
}

int send_packet(int socket_fd, const sockaddr_in* target, const int ttl, 
                icmp* packet, size_t packet_size) {
  setsockopt(socket_fd, SOL_IP, IP_TTL, &ttl, sizeof(ttl));
  size_t bytes = sendto(socket_fd, (void*)packet, packet_size, 0, (sockaddr*)target, sizeof(*target));
  return bytes;
}

void create_poll(pollfd* pfd, int socket_fd) {
  pfd->fd = socket_fd;
  pfd->events = POLLIN;
}

ssize_t receive_packet(int socket_fd, void* buffer, size_t buffer_len, sockaddr_in* src, int timeout) {
  pollfd* pfd = new pollfd();
  create_poll(pfd, socket_fd);
  int ret = poll(pfd, 1, timeout);
  if(ret < 0) {
    std::cerr << "Poll failed\n";
    return -1;
  }
  if(ret == 0) {
    return 0;
  }
  socklen_t addr_len = sizeof(*src);
  ssize_t bytes_received = recvfrom(socket_fd, buffer, buffer_len, 0, (sockaddr*)src, &addr_len);
  if(bytes_received < 0) {
    std::cerr << "Receive failed\n";
  }

  return bytes_received;
}