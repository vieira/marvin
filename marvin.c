#include "bot.h"

int
main()
{
	char *user, *command, *where, *message, *sep, *target;
	int i, j, l, sl, o = -1, start, wordcount, authenticated = 0;
	char buf[513];
	struct addrinfo hints, *res;
   
	if (config() < 0) 
		return -1;	
#ifdef MOOD
	m = VERYHAPPY;
#endif
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	getaddrinfo(host, port, &hints, &res);
	conn = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	connect(conn, res->ai_addr, res->ai_addrlen);
	raw("USER %s 0 0 :%s\r\n", nick, nick);
	raw("NICK %s\r\n", nick);
    
	while ((sl = read(conn, sbuf, 512))) {
		for (i = 0; i < sl; i++) {
			o++;
			buf[o] = sbuf[i];
			if ((i > 0 && sbuf[i] == '\n' && sbuf[i - 1] == '\r') || o == 512) {
				buf[o + 1] = '\0';
				l = o;
				o = -1;
				#ifdef DEBUG
				printf(">> %s", buf);
				#endif
				if (!strncmp(buf, "PING", 4)) {
					buf[1] = 'O';
					raw(buf);
				} else if (buf[0] == ':') {
					wordcount = 0;
					user = command = where = message = NULL;
					for (j = 1; j < l; j++) {
						if (buf[j] == ' ') {
							buf[j] = '\0';
							wordcount++;
							switch(wordcount) {
								case 1: user = buf + 1; break;
								case 2: command = buf + start; break;
								case 3: where = buf + start; break;
							}
							if (j == l - 1) continue;
							start = j + 1;
						} else if (buf[j] == ':' && wordcount == 3) {
							if (j < l - 1) message = buf + j + 1;
							break;
						}
					}
					if (wordcount < 2) continue;
					if (!strncmp(command, "001", 3) && channel != NULL) {
						raw("JOIN %s\r\n", channel);
					} else if (!strncmp(command, "PRIVMSG", 7) || !strncmp(command, "NOTICE", 6)) {
						if (where == NULL || message == NULL) continue;
						if ((sep = strchr(user, '!')) != NULL) user[sep - user] = '\0';
						if (where[0] == '#' || where[0] == '&' || where[0] == '+' || where[0] == '!') 
							target = where; else target = user;
						#ifdef SERVICES
						if (!authenticated && !strncmp(user, "NickServ", 8)) {
							raw("PRIVMSG %s :identify %s\r\n", target, password);
							authenticated = 1;
						}
						#endif
						reply(command, target, user, message);
					}
				}
			}
		}
	}
	return 0;
}
