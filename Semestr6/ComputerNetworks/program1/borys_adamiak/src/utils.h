// Borys Adamiak 337295

#pragma once
#include <assert.h>
#include <stdlib.h>
#include <cstdint>

uint16_t compute_icmp_checksum(const void *buff, int length);