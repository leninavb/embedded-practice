#include "bits.h"

uint32_t bit_set(uint32_t reg, uint8_t pos)
{
    if (pos > 31){
        return reg;
    }
    return reg | ( 1u << pos );
}

uint32_t bit_clear(uint32_t reg, uint8_t pos)
{
    if (pos > 31){
        return reg;
    }
    return reg & ~(1u << pos);
}

uint32_t bit_toggle(uint32_t reg, uint8_t pos)
{
    if (pos > 31){
        return reg;
    }
    return (reg ^ (1u << pos ));
}

uint8_t bit_read(uint32_t reg, uint8_t pos)
{
     if (pos > 31){
        return 0;
    }
    return (reg >> pos) & 1u;
}

uint32_t field_extract(uint32_t reg, uint8_t pos, uint8_t width)
{
    
    if (width == 0 || (pos + width > 32)){
        return 0u;
    }

    if(width == 32){
        return reg;
    }
    uint32_t mask = (1u << width) - 1;
    return (reg >> pos) & mask;
}

uint32_t field_write(uint32_t reg, uint8_t pos, uint8_t width, uint32_t value)
{
    if (width == 0){
        return reg;
    }
    if (pos + width > 32){
        return reg;
    }

    if (width == 32){
        return value;
    }
    uint32_t mask = ~(((1u << width)-1) << pos);
    uint32_t clean = reg & mask;
    uint32_t add = (~mask) & (value << pos);

    return clean | add;
}

uint8_t bit_count(uint32_t reg)
{
    uint8_t count = 0;

    for (uint8_t i = 0; i < 32; i++) {
        uint32_t mask = (1u << i) & reg;
        if (mask != 0) {
            count++;
        }
    }
    return count;


}

    /* Kernighan Method*/
uint8_t bit_count_kernighan(uint32_t reg)
{
    uint8_t count = 0;

    while (reg != 0) {
        reg = reg & (reg-1);
        count++;
    }

    return count;
}