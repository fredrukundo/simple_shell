#include "shell.h"

int get_length(int len)
{
	unsigned int n1;
	int lenght = 1;

	if (len < 0)
	{
		lenght++;
		n1 = len * -1;
	}
	else
	{
		n1 = len;
	}
	while (n1 > 9)
	{
		lenght++;
		n1 = n1 / 10;
	}

	return (lenght);
}
int ft_chars_comp(char s[], const char *dlim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; s[i]; i++)
	{
		for (j = 0; dlim[j]; j++)
		{
			if (s[i] == dlim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

void ft_rev_str(char *s)
{
	int count = 0, i, j;
	char *str, temp;

	while (count >= 0)
	{
		if (s[count] == '\0')
			break;
		count++;
	}
	str = s;

	for (i = 0; i < (count - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			temp = *(str + j);
			*(str + j) = *(str + (j - 1));
			*(str + (j - 1)) = temp;
		}
	}
}

char *ft_strchr(char *s, char c)
{
	unsigned int i = 0;

	for (; *(s + i) != '\0'; i++)
		if (*(s + i) == c)
			return (s + i);
	if (*(s + i) == c)
		return (s + i);
	return (NULL);
}
char *ft_itoa(int n)
{
	unsigned int n1;
	int lenght = get_length(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (lenght + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + lenght) = '\0';

	if (n < 0)
	{
		n1 = n * -1;
		buffer[0] = '-';
	}
	else
	{
		n1 = n;
	}

	lenght--;
	do {
		*(buffer + lenght) = (n1 % 10) + '0';
		n1 = n1 / 10;
		lenght--;
	}
	while (n1 > 0)
		;
	return (buffer);
}
