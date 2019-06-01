#include "error_handler.h"

#include <time.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>

static const int FOR_THREAD = 0;
static const int FOR_IPC    = 1;

//------------------------------------------------------------------------------
static const char *log_filepath = "mp_http.log";
static FILE *log_file = NULL;

sem_t log_semaphore;

//------------------------------------------------------------------------------
//#if defined DAEMON_APP

//#else
//    FILE *out_stream = stderr;
//#endif

//==============================================================================
//
//==============================================================================
int initLog() {

    if (sem_init(&log_semaphore, FOR_IPC, 1) < 0) return -1;

    log_file = fopen(log_filepath, "w+");
    if (log_file) {
        time_t t = time(NULL);
        struct tm loctm = *localtime(&t);
        const char *time_fmt = "%a, %d %b %Y %T %z";
        char timebuf[64] = {0};
        if (strftime(timebuf, 64, time_fmt, &loctm) <= 0) return -1;

        fprintf(log_file, "//==============================================================================\r\n");
        fprintf(log_file, "// MP_HTTP SERVER LOG STARTED AT: %s \r\n", timebuf);
        fprintf(log_file, "//==============================================================================\r\n");
    } else {
	return -1;
    }

    return 0;
}

//==============================================================================
//
//==============================================================================
void deinitLog() {
    sem_destroy(&log_semaphore);
    fclose(log_file);
}

//==============================================================================
//
//==============================================================================
void fprintf_mp(FILE *stream, const char *fmt, ...) {
#if !defined DAEMON_APP
    fprintf(stderr, "+");
#endif
    if (!(stream && fmt)) return;
    if (sem_wait(&log_semaphore) < 0) {
	#if defined DAEMON_APP
	    fprintf(log_file, "ERROR! Can't lock semaphore: %s\r\n", strerror(errno));
	#endif
    }
    va_list va;
    va_start (va, fmt);
    #if defined DAEMON_APP
    if (vfprintf(log_file, fmt, va) <= 0) {
	#if !defined DAEMON_APP
	    fprintf(stderr, "Can\'t write to log! %s\r\n", strerror(errno));
	#endif
    }
    #else
    vfprintf(stream, fmt, va);
    fflush(stream);
    #endif
    va_end(va);
    if (sem_post(&log_semaphore) < 0) {
	#if defined DAEMON_APP
	    fprintf(log_file, "ERROR! Can't unlock semaphore: %s\r\n", strerror(errno));
	#endif
    }
#if !defined DAEMON_APP
    fprintf(stderr, "-");
#endif
}
