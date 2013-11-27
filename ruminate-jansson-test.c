#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <ruminate.h>
#include <jansson.h>
#include <ruminate-jansson.h>

typedef char *string;
struct MyStruct {
	int i; string s; int *p;
	union { char b; void *v; } *u;
	enum MyEnum { MY_ENUM_VALUE_1, MY_ENUM_VALUE_2 } e;
	char a[3];
};
static void *deserialize_string( JsonDeserializerArgs args, void *data, GError **error ) {
	const char *str = json_string_value(args.value);
	size_t str_len = strlen(str) + 1;
	char **ret = r_mem_malloc_fn(args.type, NULL);
	*ret = r_mem_malloc_sized(char *, str_len, NULL);
	memcpy(*ret, str, str_len);
	return ret;
}
static json_t *serialize_string( JsonSerializerArgs args, void *data, GError **error ) {
	return json_string(*((char **) args.value));
}
static JsonHook string_hook = { .serializer = serialize_string, .deserializer = deserialize_string };
int main( int argc, char *argv[] ) {
	ruminate_init(argv[0], NULL);
	int ipt = 2;
	struct MyStruct foo = { .i = 1, .u = NULL, .s = "hello world!", .e = MY_ENUM_VALUE_2,
	                        .p = &ipt, .a = { 1, 2, 3 } };
	JsonState *st = json_state_new();
	json_state_add_hook(st, g_quark_from_static_string("string"), &string_hook);
	json_state_set_flags(st, JSON_FLAG_INVERTABLE);
	json_t *serialized = json_serialize(st, ruminate_get_type(foo, NULL), &foo, NULL);
	json_dumpf(serialized, stdout, 0);
	printf("\n");
	struct MyStruct *_foo = json_deserialize(st, serialized, NULL);
	printf("struct MyStruct {");
	printf(" .i = %d,", _foo->i);
	printf(" .u = %p,", _foo->u);
	printf(" .s = \"%s\",", _foo->s);
	printf(" .e = %d,", _foo->e);
	printf(" .p = %p (%d),", _foo->p, *_foo->p);
	printf(" .a = [%d, %d, %d]", _foo->a[0], _foo->a[1], _foo->a[2]);
	printf(" };\n");
	r_mem_unref(_foo->s), r_mem_unref(_foo->p), r_mem_unref(_foo);
}
