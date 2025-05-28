#include "compiler/types.h"
#include "compiler/errors.h"



u32 error_backtrace[ERROR_MAX_LEN] = {0};
u32 error_backtrace_len = 0;
u32 last_error = 0;


void add_error(u32 err) {
	last_error = err;
	if (error_backtrace_len < ERROR_MAX_LEN) {
		error_backtrace[error_backtrace_len] = err;
		error_backtrace_len++;
	}
	else {
		// move everything one position to the left
		for (int i = 1; i < error_backtrace_len; i++) {
			error_backtrace[i - 1] = error_backtrace[i];
		}
		error_backtrace[error_backtrace_len - 1] = err;
		error_backtrace_len++;
	}
}