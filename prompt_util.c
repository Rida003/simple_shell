#include "shell.h"

/**
  * print_ps1 - prints the primary shell prompt
  * @num: number that determines which errno value should be set
  */
void print_ps1(int num)
{
	char ps1[] = "RIAD$ ";
	size_t len_ps1;
	int org_error;

	org_error = errno;
	len_ps1 = _strlen(ps1);
	if (isatty(0))
		write(STDOUT_FILENO, ps1, len_ps1);
	if (num == 0)
		errno = 0;
	else
		errno = org_error;
}

/**
 * get_path - get the env path and tokenizes it into a array.
 * @modify_path: pointer to store modified path string into
 *
 * Return: array / double pointer.
 */
char **get_path(char **modify_path)
{
	char **token_ptr;
	char *path, *delim;
	unsigned int i, j, num_char;

	delim = ":";
	path = _getenv("PATH");
	num_char = _strlen(path);
	*modify_path = malloc(sizeof(char) * (num_char + 2));
	if (num_char == 0)
	{
		(*modify_path)[0] = '.';
		(*modify_path)[1] = '\0';
	}
	else
	{
		for (i = 0, j = 0; path[i] != '\0'; i++)
		{
			if (i == 0 && path[i] == ':')
			{
				(*modify_path)[j++] = '.';
				(*modify_path)[j++] = path[i];
			}
			else if (i == num_char - 1 && path[i] == ':')
			{
				(*modify_path)[j++] = path[i];
				(*modify_path)[j++] = '.';
			}
			else if (path[i] == ':' && path[i + 1] == ':')
			{
				(*modify_path)[j++] = path[i];
				(*modify_path)[j++] = '.';
			}
			else
				(*modify_path)[j++] = path[i];
		}
		for (; j < num_char + 2; j++)
			(*modify_path)[j] = '\0';
	}
	token_ptr = tokenize_str(*modify_path, delim);
	return (token_ptr);
}

/**
  * find_pathname - finds the pathname attached to the associated command
  * @path: pointer to 2d array of tokenized directories in PATH
  * @input: input to find
  * Return: Path to the input file.
  */
char *find_pathname(char **path, char *input)
{
	unsigned int i;
	DIR *directory;
	struct dirent *filename;
	int str_cmp, match_found;
	char *result;

	filename = NULL;
	match_found = 0;
	for (i = 0; path[i] != NULL; i++)
	{
		directory = opendir(path[i]);
		if (directory == NULL)
		{
			errno = EBADF;
			return (NULL);
		}
		while ((filename = readdir(directory)) != NULL)
		{
			/* TODO make strcmp function */
			str_cmp = _strcmp(filename->d_name, input);
			if (str_cmp == 0)
			{
				match_found = 1;
				break;
			}
		}
		if (match_found == 1)
			break;
		closedir(directory);
	}
	if (match_found == 1)
	{
		result = make_pathname(path[i], input);
		if (access(result, R_OK) != -1)
			errno = EACCES;
		closedir(directory);
		return (result);
	}
	errno = EBADF;
	return (NULL);
}

/**
  * make_pathname - takes result from path_name and creates a string.
  * string contains the full pathname.
  * @path: pathname
  * @file: file in the path
  * Return: pointer to an allocated string that contains the full pathname.
  */
char *make_pathname(char *path, char *file)
{
	size_t num_path, num_file;
	char *result;
	unsigned int j, k;

	num_path = _strlen(path);
	num_file = _strlen(file);
	result = malloc(sizeof(char) * (num_path + num_file + 2));
	if (result == NULL)
		return (NULL);
	for (j = 0; j < num_path; j++)
		result[j] = path[j];
	result[j++] = '/';
	for (k = 0; k < num_file; k++)
		result[j + k] = file[k];
	result[j + k] = '\0';
	return (result);
}
/**
  * _getenv - gets the value of the environment variable
  * @name: variable to find
  * Return: pointer to the value of the environment variable.
  */
char *_getenv(const char *name)
{
	unsigned int i, j;

	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; environ[i][j] != '=' && environ[i][j] == name[j] && name[j]; j++)
			;
		if (environ[i][j] == '=' && name[j] == '\0')
			return (&environ[i][++j]);
	}
	return (NULL);
}
