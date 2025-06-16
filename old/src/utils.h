#ifndef ZLISP_UTILS_H
#define ZLISP_UTILS_H

#include <stdio.h>

#define LOG(format, ...) fprintf(stdout, "LOG: %s:%d " format "\n", __FILE__, __LINE__, ##__VA_ARGS__);
#define ERR(format, ...) fprintf(stderr, "ERR: %s:%d " format "\n", __FILE__, __LINE__, ##__VA_ARGS__);

#endif // ZLISP_UTILS_H
