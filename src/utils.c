#include <stdio.h>
#include <string.h>
#include <stdint.h>

uint8_t isin(uint8_t ch, char* str) {
    size_t len = strlen(str);
    for (size_t i = 0; i < len; ++i) {
        if (ch == str[i]) return 1;
    }
    return 0;
}

long get_file_size(const char* file_path) {
    FILE* fp = fopen(file_path, "rb");

    if (fp == NULL) {
        perror("Errpr opening file");
        return -1;
    }

    if (fseek(fp, 0, SEEK_END) != 0) {
        perror("Error seeking file-end");
        fclose(fp);
        return -1;
    }

    long file_size = ftell(fp);

    if (file_size == -1) {
        perror("Could not get file size");
        fclose(fp);
        return -1;
    }

    fclose(fp);
    return file_size;
}
