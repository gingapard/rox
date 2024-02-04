#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>

#include "../../src/net.h"
#include "../../src/lexer.h"
#include "../../src/utils.h"

int main(void) {
	const char* url = "https://www.gnu.org";
	const char* output_path = "gnu.html";

	int result = download_site(url, output_path);
	if (result == 0) {
		printf("Website download -> OK\n");
	} else {
		fprintf(stderr, "Website download -> ERROR\n");
	}

	FILE* fp = fopen(output_path, "r");

	long file_size = get_file_size(output_path);
	char* buffer = (char*)malloc(get_file_size(output_path) + 1);

	if (buffer == NULL) {
		fclose(fp);
		perror("could not alloc memory");
		return 1;
	}

	size_t read_size = fread(buffer, 1, file_size, fp);
	if (read_size != file_size) {
		fclose(fp);
		free(buffer);
		perror("could not read file");
		return 1;
	}

	buffer[file_size] = '\0';

	// init lexer
	Lexer lexer;

	lexer.position = 0;
	lexer.input = strdup(buffer);
	lexer.ch = lexer.input[lexer.position];
	// init lexer

	Token token;
	while ((token = next_token(&lexer)).type != EOF_TYPE) {
		printf("%d: %s\n", token.type, token.content);
	}

	free(lexer.input);
	fclose(fp);
    return result;
}
