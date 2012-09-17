#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>

#define SERVICES
#undef DEBUG
#ifndef MOOD
#define MOOD
typedef enum {
	DEPRESSED,
	SAD,
	NORMAL,
	HAPPY,
	VERYHAPPY
} mood;
mood m;
#endif
#ifndef CONFIG
#define CONFIG
char nick[128], password[128], host[128], channel[128], port[128];
#endif
int conn;
char sbuf[512];
int vsnprintf(char *str, size_t size, const char *format, va_list ap);
int config(void);
void raw(char *fmt, ...);
void reply(char *command, char *target, char *user, char *message);
