// Borys Adamiak 337295
#include <iostream>
#include <cstdint>
#include <string>
#include <unistd.h>
#include <sys/time.h>
#include <vector>
#include <unordered_set>
#include "icmp.h"
#include "timer.h"

#define TIMEOUT_MS 1000


// sprawdzamy czy adres podany jako input jest rzeczywistym adresem
bool check_valid_input(std::string ip) {
  if(ip.size() < 7 or ip.size() > 15) {
    return false;
  }
  uint8_t curr_idx = 0;
  std::string curr_byte = "";
  for(int i = 0; i < (int)ip.size(); i++) {
    if(ip[i] <= '9' && ip[i] >= '0') {
      curr_byte += ip[i];
      if(curr_byte.size() > 3) return false;
    } else if(ip[i] == '.') {
      if(std::stoi(curr_byte) > 255 || curr_byte.size() == 0) return false;
      curr_idx++;
      curr_byte = "";
      if(curr_idx > 3) return false;
    } else {
      return false;
    }
  }
  if(curr_byte.size() == 0 || std::stoi(curr_byte) > 255) return false;
  return true;
}

int main(int argc, char** argv) {
  Timer timer;
  if(argc < 2) {
    std::cerr << "No argument provided\n";
    return 1;
  }
  if(argv[1] == NULL) {
    std::cerr << "No argument provided\n";
    return 1;
  }
  std::string input_ip = argv[1];
  if(!check_valid_input(input_ip)) {
    std::cerr << "Input not valid. Provide correct ip address\n";
    return 1;
  }

  int socket_fd = create_socket();
  if(socket_fd < 0) {
    std::cerr << "Socket failure\n";
    return 1;
  }
  sockaddr_in target{};
  target.sin_family = AF_INET;
  inet_pton(AF_INET, input_ip.c_str(), &target.sin_addr);
  bool is_destination = false;
  int64_t packet_send_time[90];
  
  for(int ttl = 1; ttl <= 30 && !is_destination; ttl++) {
    std::unordered_set<std::string> ips;
    icmp headers[3];
    double rtt = 0.0;
    int responses = 0;
    std::cout << ttl << ". ";
    for(int i = 0; i < 3; i++) {
      create_echo_packet(&headers[i], ttl, i);
      packet_send_time[(ttl-1)*3+i] = timer.now_precise();
      if(send_packet(socket_fd, &target, ttl, &headers[i], sizeof(headers[i])) < 0) {
        std::cerr << "Failed to send packet\n";
        return 1;
      }
    }

    sockaddr_in sender{};
    timer.reset();
    while(timer.elapsed() < TIMEOUT_MS && responses < 3) {
      unsigned char buffer[IP_MAXPACKET];
      timeval start{}, end{};
      gettimeofday(&start, nullptr);
      ssize_t received_bytes = receive_packet(socket_fd, buffer, sizeof(buffer), &sender, TIMEOUT_MS);
      gettimeofday(&end, nullptr);

      if(received_bytes > 0) {
        ip* ip_header = (ip*)buffer;
        const ssize_t ip_header_len = 4 * (ssize_t)(ip_header->ip_hl);
        icmp* icmp_packet = (icmp*)(buffer+ip_header_len);
        icmp* icmp_original = (icmp*)(buffer+ip_header_len+sizeof(icmp));
        if(icmp_packet->icmp_type == ICMP_TIME_EXCEEDED && 
          icmp_original->icmp_hun.ih_idseq.icd_id == getpid() &&
          icmp_original->icmp_hun.ih_idseq.icd_seq >= (ttl-1)*3 &&
          icmp_original->icmp_hun.ih_idseq.icd_seq <= (ttl-1)*3 + 2) {
          rtt += (double)(timer.now_precise() - packet_send_time[icmp_original->icmp_hun.ih_idseq.icd_seq]);
          responses++;
          char sender_ip[INET_ADDRSTRLEN];
          inet_ntop(AF_INET, &(sender.sin_addr), sender_ip, sizeof(sender_ip));
          ips.insert(sender_ip);
        } else if(icmp_packet->icmp_type == ICMP_ECHOREPLY &&
          icmp_packet->icmp_hun.ih_idseq.icd_id == getpid() &&
          icmp_packet->icmp_hun.ih_idseq.icd_seq >= (ttl-1)*3 &&
          icmp_packet->icmp_hun.ih_idseq.icd_seq <= (ttl-1)*3 + 2) {
            rtt += (double)(timer.now_precise() - packet_send_time[icmp_original->icmp_hun.ih_idseq.icd_seq]);
            responses++;
            char sender_ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(sender.sin_addr), sender_ip, sizeof(sender_ip));
            ips.insert(sender_ip);
            is_destination = true;
          } else {
          continue;
        }
      }
    }

    if(ips.empty()) {
      std::cout << "*\n";
      continue;
    }
    for(std::string _ip : ips) {
      std::cout << _ip << " ";
    }
    if(responses < 3) {
      std::cout << "???\n";
    } else {
      double avg = rtt / (double)responses;
      printf("%.3lf ms\n", avg);
    }

    if(is_destination) break;
  }
  
  close(socket_fd);
  return 0;
}