#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

#include <ruminate.h>

void abort_with_backtrace( const char *message ) {
	RFrameList *frames = ruminate_backtrace(NULL);

	fprintf(stderr, "abort(): %s\n", message == NULL ? "" : message);
	size_t frames_len = r_frame_list_size(frames, NULL);
	for( size_t i = 0; i < frames_len; i++ ) {
		RFrame *frame = r_frame_list_at(frames, i, NULL);
		RString *fname = r_frame_function_name(frame, NULL);
		RString *mname = r_frame_module_name(frame, NULL);
		RString *cuname = r_frame_compile_unit_name(frame, NULL);
		uint32_t line = r_frame_line(frame, NULL);
		fprintf(
			stderr,
			"\tat %s(%s, %s:%d)\n",
			r_string_bytes(fname),
			r_string_bytes(mname),
			r_string_bytes(cuname),
			line
		);
		r_string_unref(cuname);
		r_string_unref(mname);
		r_string_unref(fname);
	}

	r_frame_list_unref(frames);
	abort();
}

void bar( int i ) {
	if( i < 2 ) {
		bar(i + 1);
	} else {
		abort_with_backtrace("Hello World!");
	}
}

void foo() {
	bar(0);
}

int main( int argc, char *argv[] ) {
	ruminate_init(argv[0], NULL);
	foo();
}
