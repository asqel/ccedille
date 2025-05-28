#include <stdio.h>

char *uti_read_file(char *path) {
	FILE *f = fopen(path, "r");
	if (f == NULL)
		return (NULL);
	int len = 0;

	fseek(f, 0, SEEK_END);
	len = ftell(f);
	fseek(f, 0, SEEK_SET);

	char *content = malloc(sizeof(char) * (len + 1));
	fread(content, len, sizeof(char), f);
	content[len] = '\0';

	fclose(f);
	return (content);
}
