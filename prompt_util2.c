#include "shell.h"

/**
  * free_shell_t - frees elements in shell_t struct
  * @shell_ptrs: structure of malloced elements
  */
void free_shell_t(shell_t *shell_ptrs)
{
	free(shell_ptrs->path_values);
	free(shell_ptrs->input);
	free(shell_ptrs->input_token);
	free(shell_ptrs->modify_path);
}

/**
  * p_commanderr - prints error for failed command
  * @command: command that was submitted by user
  * @filename: name of the file being run
  */
void p_commanderr(char *command, char *filename)
{
	char *error_message;
	char *error = ": command not found\n";
	size_t num_char, i;
	(void)filename;

	num_char = _strlen(error) + _strlen(command);
	error_message = malloc(sizeof(char) * (++num_char));

	i = 0;
	while (*command != '\0')
		error_message[i++] = *command++;
	while (*error != '\0')
		error_message[i++] = *error++;
	error_message[i] = '\0';
	write(STDERR_FILENO, error_message, num_char);
	free(error_message);
}
