#include <stdio.h>
#include <curl/curl.h>

#include "net.h"

size_t write_callback(void *contents, size_t size, size_t nmemb, FILE *stream) {
    return fwrite(contents, size, nmemb, stream);
}

int download_site(const char* url, const char* output_path) {
    CURL* curl;
    FILE* fp;
    CURLcode result;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        fp = fopen(output_path, "wb");

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

        result = curl_easy_perform(curl);
        if (result != CURLE_OK)
            fprintf(stderr, "failed function: curl_easy_perform()\n");

        curl_easy_cleanup(curl);
        fclose(fp);
    } else {
        fprintf(stderr, "Failed to init libcurl\n");
        return 1;
    }

    curl_global_cleanup();

    return 0;
}
