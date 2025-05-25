#include "downloader.h"

int main(int argc, const char* argv[]) {
  input i = check_data_validity(argc, argv);
  int sockfd = create_socket();
  sockaddr_in server_addr = setup_server_address(i);
  download_file(i, sockfd, server_addr);
  close(sockfd);
  cerr << "File downloaded\n";
  return 0;
}
