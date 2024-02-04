#ifndef NET_H
#define NET_H

#include <stdio.h>

size_t write_callback(void* contents, size_t size, size_t nmemb, FILE *stream);
int download_site(const char* url, const char* output_path);

#endif
