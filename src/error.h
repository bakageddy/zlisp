#ifndef ZLISP_ERROR_H
#define ZLISP_ERROR_H

#include "string.h"

typedef enum {
	OK = 0,
	OUT_OF_BOUNDS,
	UNEXPECTED_PARAMETER
} zlisp_ekind_t;

typedef struct {
	zlisp_ekind_t kind;
	zlisp_string_t string;
} zlisp_error_t;

#endif // ZLISP_ERROR_H
