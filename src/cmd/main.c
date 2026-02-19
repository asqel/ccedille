#include "compiler/tokens.h"
#include "utils.h"
#include <stdio.h>

static int main_test() {
	char *text = uti_read_file("test/test.cdy");
	free(text);
	return 0;
}

int main() {
	main_test();
	return 0;
}