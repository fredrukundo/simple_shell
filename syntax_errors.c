#include "shell.h"

int count_repeated_char(char *str, int i)
{
	if (*(str - 1) == *str)
		return (count_repeated_char(str - 1, i + 1));

	return (i);
}

int sep_error(char *input, int i, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (sep_error(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = count_repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = count_repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (sep_error(input + 1, i + 1, *input));
}

int char_first_index(char *s, int *i)
{

	for (*i = 0; s[*i]; *i += 1)
	{
		if (s[*i] == ' ' || s[*i] == '\t')
			continue;

		if (s[*i] == ';' || s[*i] == '|' || s[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

void syntax_error_display(sh_data *datas, char *input, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = ft_itoa(datas->i);
	length = ft_strlen(datas->arg_v[0]) + ft_strlen(counter);
	length += ft_strlen(msg) + ft_strlen(msg2) + ft_strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	ft_strcpy(error, datas->arg_v[0]);
	ft_strcat(error, ": ");
	ft_strcat(error, counter);
	ft_strcat(error, msg2);
	ft_strcat(error, msg);
	ft_strcat(error, msg3);
	ft_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

int syntax_errors(sh_data *datas, char *s)
{
	int start = 0;
	int f_char = 0;
	int i = 0;

	f_char = char_first_index(s, &start);
	if (f_char == -1)
	{
		syntax_error_display(datas, s, start, 0);
		return (1);
	}

	i = sep_error(s + start, 0, *(s + start));
	if (i != 0)
	{
		syntax_error_display(datas, s, start + i, 1);
		return (1);
	}

	return (0);
}
