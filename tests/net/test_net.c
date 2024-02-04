#include <stdio.h>
#include <curl/curl.h>

#include "../../src/net.h"

int main(void) {
	const char* url = "https://www.gnu.org";
	const char* output_path = "gnu.html";

	int result = download_site(url, output_path);
	if (result == 0) {
		printf("Website download -> OK\n");
	} else {
		fprintf(stderr, "Website download -> ERROR\n");
	}

    return result;
}
