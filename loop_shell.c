#include "shell.h"

char *ft_read_line(int *end_file)
{
	char *input = NULL;
	size_t bufsize = 0;

	*end_file = getline(&input, &bufsize, stdin);

	return (input);
}

char *remove_comment(char *input)
{
	int i, to_up;

	to_up = 0;
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '#')
		{
			if (i == 0)
			{
				free(input);
				return (NULL);
			}

			if (input[i - 1] == ' ' || input[i - 1] == '\t' || input[i - 1] == ';')
				to_up = i;
		}
	}

	if (to_up != 0)
	{
		input = ft_realloc(input, i, to_up + 1);
		input[to_up] = '\0';
	}

	return (input);
}

void loop_shell(sh_data *datash)
{
	int loop, end_file;
	char *str_inpt;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "my_shell($) ", 11);
		str_inpt = ft_read_line(&end_file);
		if (end_file != -1)
		{
			str_inpt = remove_comment(str_inpt);
			if (str_inpt == NULL)
				continue;

			if (syntax_errors(datash, str_inpt) == 1)
			{
				datash->status = 2;
				free(str_inpt);
				continue;
			}
			str_inpt = replace_str_var(str_inpt, datash);
			loop = cmd_split(datash, str_inpt);
			datash->i += 1;
			free(str_inpt);
		}
		else
		{
			loop = 0;
			free(str_inpt);
		}
	}
}
