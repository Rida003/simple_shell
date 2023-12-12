#include "shell.h"

/**
  * _strtok - tokenizes a string
  * @str: string to tokenize
  * @delim: string that contains the delimiters
  * Return: pointer to position in string of a null terminated word.
  */
char *_strtok(char *str, const char *delim)
{
	static char *begin, *end_str, *end;
	unsigned int i, j;
	int word_found = 0;

	if (str == NULL)
	{
		if (begin == NULL || end == NULL)
			return (NULL);
		str = end + 1;
	}
	else
		end_str = str + _strlen(str);
	for (i = 0; str + i < end_str; i++)
	{
		for (j = 0; delim != NULL && delim[j] != '\0'; j++)
		{
			if (str[i] == delim[j])
			{
				if (word_found == 1)
				{
					str[i] = '\0';
					end = str + i;
					return (begin);
				}
				break;
			}
		}
		if (delim[j] == '\0' && word_found == 0)
		{
			word_found = 1;
			begin = str + i;
		}
	}
	end = NULL;
	if (word_found == 1)
		return (begin);
	return (NULL);
}
