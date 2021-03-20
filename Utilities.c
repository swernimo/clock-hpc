#include "Utilities.h"

uint8_t SetBit(uint8_t data, int position){
    return (data |= 1 << position);
}

uint8_t ClearBit(uint8_t data, int position){
    return (data &= ~(1 << position));
}

uint8_t ToggleBit(uint8_t data, int position){
    return (data ^= 1 << position);
}