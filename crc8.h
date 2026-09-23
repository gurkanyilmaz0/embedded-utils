#ifndef CRC8_H
#define CRC8_H

#include <stdint.h>
#include <stddef.h>

uint8_t CRC8_Calculate(const uint8_t *data, size_t len);

#endif
