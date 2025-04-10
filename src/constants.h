#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdio.h>
#include <limits.h>

#define KEY_LENGTH BUFSIZ

#ifdef PATH_MAX
#define PATH_LENGTH PATH_MAX
#else
#define PATH_LENGTH 260
#endif

#endif // CONSTANTS_H