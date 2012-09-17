#include "bot.h"
#include "modules.h"

int
main()
{
	DIR *modules_dir;
	struct dirent *modules;
	module loaded_modules[64];
	int i = 0;

	modules_dir = opendir(".");
	if (!modules_dir) {
		puts ("FAIL");
		return -1;
	}
	errno = 0;
	while ((modules = readdir(modules_dir))) {
		if (strncmp((modules->d_name+(strlen(modules->d_name)-3)), ".py", 3) == 0) {	
			strcpy(loaded_modules[i].name, modules->d_name);
			strcpy(loaded_modules[i].handler, "python ");
			printf("%s\n", loaded_modules[i++].name);
		} else if (strncmp((modules->d_name+(strlen(modules->d_name)-4)), ".scm", 4) == 0) {
			strcpy(loaded_modules[i].name, modules->d_name);
			strcpy(loaded_modules[i].handler, "guile ");
			printf("%s\n", loaded_modules[i++].name);
		}
	}
	if (errno) {
		printf("readdir failed with error %d\n", errno);
		return -2;
	}
	closedir(modules_dir);
	return 0;
}
