#include "shell.h"

void assign_line(char **line, size_t *n, char *buf, size_t l)
{

	if (*line == NULL)
	{
		if  (l > BUFFER_SIZE)
			*n = l;

		else
			*n = BUFFER_SIZE;
		*line = buf;
	}
	else if (*n < l)
	{
		if (l > BUFFER_SIZE)
			*n = l;
		else
			*n = BUFFER_SIZE;
		*line = buf;
	}
	else
	{
		ft_strcpy(*line, buf);
		free(buf);
	}
}

ssize_t ft_get_line(char **line, size_t *n, FILE *stream)
{
	int i;
	static ssize_t inpt;
	ssize_t retval;
	char *buffer;
	char t = 'a';

	if (inpt == 0)
		fflush(stream);
	else
		return (-1);
	inpt = 0;

	buffer = malloc(sizeof(char) * BUFFER_SIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && inpt == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && inpt != 0)
		{
			inpt++;
			break;
		}
		if (inpt >= BUFFER_SIZE)
			buffer = ft_realloc(buffer, inpt, inpt + 1);
		buffer[inpt] = t;
		inpt++;
	}
	buffer[inpt] = '\0';
	assign_line(line, n, buffer, inpt);
	retval = inpt;
	if (i != 0)
		inpt = 0;
	return (retval);
}
