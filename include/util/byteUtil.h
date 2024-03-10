
#ifndef BYTE_UTIL_H
#define BYTE_UTIL_H

#include <stdint.h>

namespace util {
    
void setBit(uint8_t* byte, int idx, bool value) {
    if(value) {
        *byte |= (1 << idx);
    }
    else {
        *byte &= ~(1 << idx);
    }
}
	
}

#endif // BYTE_UTIL_H
