#include "bot.h"

void raw(char *fmt, ...) 
{
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(sbuf, 512, fmt, ap);
	va_end(ap);
	#ifdef DEBUG
	printf("<< %s", sbuf);
	#endif
	write(conn, sbuf, strlen(sbuf));
}
