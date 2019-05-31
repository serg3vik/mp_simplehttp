#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>

extern sem_t log_semaphore;

//------------------------------------------------------------------------------

int initLog();
void deinitLog();
void fprintf_mp(FILE *stream, const char *fmt, ...);

#endif // ERROR_HANDLER_H

