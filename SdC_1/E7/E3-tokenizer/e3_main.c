#include "e3.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int score, trials;

void print_token_list(char **tokens, int cnt) {
	int i;
	printf("[");
	for (i=0; i<cnt; ++i)
		printf("%s%s", i==0 ? "":", ", tokens[i]);
	printf("]\n");
}

void deallocate_token_list(char **tokens, int cnt) {
	int i;
	for (i=0; i<cnt; ++i)
		free(tokens[i]);
	free(tokens);
}

int match(char **res, const char *str, const char *delim, int cnt) {
	char* buf = malloc(strlen(str)+1);
	strcpy(buf, str);
	char *token = strtok(buf, delim);
	int i=0;
	while (token != NULL) {
		if (strcmp(token, res[i++])) {
			free(buf);
			return 0;
		}
		token = strtok(NULL, delim);
	}
	free(buf);
	return 1;
}

void test(const char *str, const char *delim) {
	trials++;
	int cnt;
	char **array = tokenize(str, delim, &cnt);
	int res = match(array, str, delim, cnt);
	score += res;
	printf("Test %d: \"%s\" -> %s %d tokens: ", trials, str, res ? "[OK]":"[ERR]", cnt);
	print_token_list(array, cnt);
	deallocate_token_list(array, cnt);
}

int main() {
	
	test("la luna nel piatto", " ");
	test("Houston, we have a problem", ", ");
	test(" , # ", "#, ");

	printf("Risultato: %d/%d\n", score, trials);
}
