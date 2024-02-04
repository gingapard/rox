#include <string.h>
#include <stdint.h>

uint8_t isin(uint8_t ch, char* identifiers) {
    size_t len = strlen(identifiers);
    for (size_t i = 0; i < len; ++i) {
        if (ch == identifiers[i]) return 1;
    }
    return 0;
}

