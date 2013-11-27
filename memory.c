#include <ruminate.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char *argv[] ) {
	(void) argc;

	ruminate_init(argv[0], NULL);

	const char *src_str = "Hello World!";
	size_t src_str_len = strlen(src_str) + 1;
	void *str = r_mem_malloc_sized(char *, src_str_len, NULL);
	memcpy(str, src_str, src_str_len);

	RType *str_type = r_mem_type(str);
	RString *str_type_name = r_type_name(str_type, NULL);

	printf("(%s) \"%s\"\n", r_string_bytes(str_type_name), str);

	r_string_unref(str_type_name);
	r_type_unref(str_type);
	r_mem_unref(str);
}
