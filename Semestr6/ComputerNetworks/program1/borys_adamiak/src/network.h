// Borys Adamiak 337295
#pragma once
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdint>
#include <iostream>

int create_socket();
void check_socket(int socket_fd);
void print_as_bytes(unsigned char* buffer, ssize_t buffer_len);