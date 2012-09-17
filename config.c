#include "bot.h"

int
config()
{
	char *keyword[] = { "nick", "password", "host", "channel", "port" };
	ssize_t len;
	int i, valid[5];
	char tmp[128], *str[] = { nick, password, host, channel, port };
	char file[] = "marvin.conf";
	FILE *fp = fopen(file, "r");
	memset(valid, 0, 5);
	if (fp == NULL) { 
		printf("[Error] Cannot read the configuration file.\n");
		return -2; 
	}
	while (fgets(tmp, 128, fp)) {
		len = strlen(tmp);
		for (i = 0; i < 5; ++i) {
			if (strncmp(keyword[i], tmp, strlen(keyword[i])) == 0) {
				if (tmp[len - 1] == '\n') tmp[--len] = 0;
				sprintf(str[i], "%s", &tmp[strlen(keyword[i])+1]);
				valid[i] = 1;
				break;
			}
		}
	}
	fclose(fp);
	for (i = 0; i < 5; ++i) {
		if (!valid[i]) {
			printf("[Error] %s not defined. Please edit %s.\n",
					keyword[i], file);
			return -3;
		}
	}
	return 0;
}
