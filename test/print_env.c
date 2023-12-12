#include "shell.h"

/**
  * print_env - prints out the current environment
  * @ptrs: structure containing all malloced memory
  */
void print_env(shell_t *ptrs)
{
	unsigned int i, k;
	char newline = '\n';

	(void)ptrs;
	if (environ == NULL)
		return;
	for (i = 0; environ[i] != NULL; i++)
	{
		k = _strlen(environ[i]);
		if (k != 0)
		{
			write(STDOUT_FILENO, environ[i], k);
			write(STDOUT_FILENO, &newline, 1);
		}
	}
	errno = 0;
}
