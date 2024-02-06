#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

uint8_t is_in(uint8_t ch, char* str) {
    size_t len = strlen(str);
    for (size_t i = 0; i < len; ++i) {
        if (ch == str[i]) return 1;
    }
    return 0;
}

char* str_x_dup(char* str) {
    size_t len = strlen(str);
    char* alloced_str = (char*)malloc(len + 1);
    if (alloced_str == NULL) {
        fprintf(stderr, "could not allocate memory");
        return NULL;
    }

    for (size_t i = 0; i < len; ++i) {
        alloced_str[i] = str[i]; 
    }

    alloced_str[len + 1] = '\0';
    return alloced_str;
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
