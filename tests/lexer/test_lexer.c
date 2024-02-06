#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../src/lexer.h"
#include "../../src/utils.h"

int main(int argc, char** argv) {

	char* input = "<div class=\"testtext\">Hello</div> JOIN</a>awdawd<a>";

	char* path = "gnu.html";
	FILE* fp = fopen(path, "r");

	long file_size = get_file_size(path);
	char* buffer = (char*)malloc(get_file_size(path) + 1);

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
	lexer.input = (char*)malloc(strlen(buffer) + 1);
	strcpy(lexer.input, buffer);
	lexer.input[strlen(buffer)] = '\0';

	lexer.position = 0;
	lexer.ch = lexer.input[lexer.position];
	// init lexer

	Token token;
	while ((token = next_token(&lexer)).type != EOF_TYPE) {
		printf("%d: %s\n", token.type, token.content);
	}

	free(lexer.input);
	return 0;
}
