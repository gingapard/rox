#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <string.h>

uint8_t is_in(uint8_t ch, char* str);
char* str_x_dup(char* str);
long get_file_size(const char* file_path);

#endif
