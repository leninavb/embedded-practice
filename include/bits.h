#ifndef BITS_H
#define BITS_H

#include <stdint.h>

uint32_t bit_set(uint32_t reg, uint8_t pos);
uint32_t bit_clear(uint32_t reg, uint8_t pos);
uint32_t bit_toggle(uint32_t reg, uint8_t pos);
uint8_t  bit_read(uint32_t reg, uint8_t pos);
uint32_t field_extract(uint32_t reg, uint8_t pos, uint8_t width);
uint32_t field_write(uint32_t reg, uint8_t pos, uint8_t width, uint32_t value);
uint8_t  bit_count(uint32_t reg);
uint8_t bit_count_kernighan(uint32_t reg);

#endif