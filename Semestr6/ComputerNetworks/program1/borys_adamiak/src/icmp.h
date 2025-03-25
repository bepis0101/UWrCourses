#include "utils.h"
#include "network.h"
#include <netinet/ip_icmp.h>
#include <poll.h>
#include <unistd.h>


void create_echo_packet(icmp* header, uint16_t ttl, uint16_t seq);
int send_packet(int socket_fd, const sockaddr_in* target, const int ttl, 
                icmp* packet, size_t packet_size);
void create_poll(pollfd* pfd, int socket_fd);
ssize_t receive_packet(int socket_fd, void* buffer, size_t buffer_len, sockaddr_in* src, int timeout);