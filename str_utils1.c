#include "shell.h"

char *ft_strdup(const char *s)
{
	char *new;
	size_t len;

	len = ft_strlen(s);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, s, len + 1);
	return (new);
}


int ft_strlen(const char *str)
{
	int i;

	for (i = 0; str[i] != 0; i++)
	{
	}
	return (i);
}

char *ft_strtok(char str[], const char *dlim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (ft_chars_comp(str, dlim))
			return (NULL);
		splitted = str;
		i = ft_strlen(str);
		str_end = &str[i];
	}
	str_start = splitted;
	if (str_start == str_end)
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		for (i = 0; dlim[i]; i++)
		{
			if (*splitted == dlim[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (str_start);
}

int ft_isdigit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}
