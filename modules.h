#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>

typedef struct {
	char name[128];
	char handler[64];
} module;
