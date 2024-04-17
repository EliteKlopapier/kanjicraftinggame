#include "byteUtil.h"

namespace util {

void setBit(uint8_t* byte, int idx, bool value) {
    if(value) {
        *byte |= (1 << idx);
    }
    else {
        *byte &= ~(1 << idx);
    }
}

} // namespace util