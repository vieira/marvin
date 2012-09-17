#include "bot.h"

void reply(char *command, char *target, char *user, char *message) {
	if (!strncmp(message, "!ola", 4) || !strncmp(message, "!hello", 5)) {
		#ifndef MOOD
		raw("%s %s :%s: ola\r\n", command, target, user);
		#else
		switch (m) {
			case DEPRESSED:
				raw("%s %s :Life sucks :X\r\n", command, 
						target);
				m++;
				break;
			case SAD:
				raw("%s %s :Meh... Hello.\r\n", command,
						target);
				m++;
				break;
			case NORMAL:
				raw("%s %s :%s: ola\r\n", command, target,
						user);
				m++;
				break;
			case HAPPY:
				raw("%s %s :%s: alo alo. what's up?\r\n", 
						command, target, user);
				m++;
				break;
			case VERYHAPPY:
				raw("%s %s :%s: yay! ola :D\r\n", command, 
						target,	user);
				break;
			default:
				raw("%s %s :Feeling weird today.\r\n",
						command, target);
				break;
		}	
		#endif	
	} else if (!strncmp(message, "!topic", 6)) {
		#ifndef SERVICES
			raw("TOPIC %s :%s\r\n", target, message+7);
		#else
			raw("%s %s :Won't. Maybe tomorrow. Try ChanServ\r\n", 
					command, target);
			#ifdef MOOD
			if (m > SAD) m--;
			#endif
		#endif
	} else if (!strncmp(message, "!join", 5)) {
		#ifdef MOOD
		if (m > SAD)
			raw("JOIN %s\r\n", message+6);
		else
			raw("%s %s :Won't join. Too sad now...\r\n", command,
				       	target);
		#else
		raw("JOIN %s\r\n", message+6);
		#endif
	} else if (!strncmp(message, "!part", 5)) {
		if (!strncmp(message+6, channel, strlen(channel))) 
			raw("%s %s :This is my home.\r\n", command, target);
		else 
			raw("PART %s\r\n", message+6);
		#ifdef MOOD
		if (m > DEPRESSED) m--;
		#endif
	} else if (!strncmp(message, "!marvin", 7)) {
		#ifdef MOOD
		switch (m) {
			case DEPRESSED:
			case SAD:
				raw("%s %s :I'm just a stupid robot :(\r\n", 
						command, target);
				break;
			case NORMAL:
				raw("%s %s :I'm marvin, the robot.\r\n",
						command, target);
				break;
			case HAPPY:
			case VERYHAPPY:
				raw("%s %s :I'm a very smart robot that will dominate the world.\r\n", command, target);
				break;
		}		
		#else
		raw("%s %s :I'm a very smart robot that will dominate the world.\r\n", command, target);
		#endif
	} else if (!strncmp(message, "!wait", 5)) {
		raw("%s %s :Wait for it...\r\n", command, target);
		sleep(3);
		raw("%s %s :It will be legendary!\r\n", command, target);
 		#ifdef MOOD
		if (m < VERYHAPPY) m++;
		#endif
	} else if (!strncmp(message, "!units", 6) && strlen(message) > 8) {
		FILE *fp;
		char ask[128] = "units -t ";
		char reply[256];

		size_t len = strlen(&message[6]);
		strncat(ask, &message[6], len-2);
		fp = popen(&ask[0], "r");
		if (fp == NULL) {
			return;
		}
		while (fgets(reply, 256, fp) != NULL) {
			raw("%s %s :%s: %s", command, target, user, reply);
		}
		pclose(fp);
		#ifdef MOOD
		if (m > DEPRESSED) m--;
		#endif
	} else if (!strncmp(message, "!factor", 7) && strlen(message) > 9) {
		FILE *fp;
		char ask[128] = "factor ";
		char reply[256];

		size_t len = strlen(&message[6]);
		strncat(ask, &message[6], len-2);
		fp = popen(&ask[0], "r");
		if (fp == NULL)	return;
		
		while (fgets(reply, 256, fp) != NULL) {
			raw("%s %s :%s: %s", command, target, user, reply);
		}
		pclose(fp);
		#ifdef MOOD
		if (m > DEPRESSED) m--;
		#endif
	} else if (!strncmp(message, "!date", 5)) {
		FILE *fp;
		char reply[256];

		fp = popen("date", "r");
		if (fp == NULL) {
			return;
		}
		while(fgets(reply, 256, fp) != NULL) {
			raw("%s %s :%s: %s", command, target, user, reply);
		}
		pclose(fp);
	}
}
