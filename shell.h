#ifndef SHELL_H
#define SHELL_H

/* struct declarations */
typedef struct cmds {
	struct cmds *next;
	int (*run_cmd)(char *);
} cmd_t;

/* header files */
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#endif
