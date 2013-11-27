typedef struct {
	enum {
		TYPE_INT,
		TYPE_TYPEDEF,
		TYPE_POINTER,
		TYPE_STRUCT
	} type;
	const char *name;
	size_t size;
} type_t;

typedef struct {
	type_t type;
	type_t *real;
} typedef_t;

typedef struct {
	type_t type;
	type_t *referent;
} pointer_t;

typedef struct {
	const char *name;
	size_t offset;
	const type_t *referent;
} field_t;

typedef struct {
	type_t type;
	const char *name;
	size_t nfields;
	const field_t fields[];
} struct_t;

const type_t *get_type( const char *tynam );
void release_type( const type_t *typ );
