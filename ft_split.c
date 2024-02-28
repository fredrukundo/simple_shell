#include "shell.h"

void next_cmd(t_sep_list **list_s, t_list_line **list_l, sh_data *datash)
{
	int loop_sep;
	t_sep_list *ls_s;
	t_list_line *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (datash->status == 0)
		{
			if (ls_s->sep == '&' || ls_s->sep == ';')
				loop_sep = 0;
			if (ls_s->sep == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->sep == '|' || ls_s->sep == ';')
				loop_sep = 0;
			if (ls_s->sep == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}
char *ft_swap(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}

void add_sep_cmd_line(t_sep_list **head_s, t_list_line **head_l, char *input)
{
	int i;
	char *line;

	input = ft_swap(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_separator_at_end(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			add_separator_at_end(head_s, input[i]);
			i++;
		}
	}

	line = ft_strtok(input, ";|&");
	do {
		line = ft_swap(line, 1);
		add_line_at_end(head_l, line);
		line = ft_strtok(NULL, ";|&");
	} while (line != NULL);

}

int cmd_split(sh_data *datash, char *input)
{

	t_sep_list *head_s, *list_s;
	t_list_line *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	add_sep_cmd_line(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = line_splitting(datash->input);
		loop = execute_line(datash);
		free(datash->args);

		if (loop == 0)
			break;

		next_cmd(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_separator_list(&head_s);
	free_line(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

char **line_splitting(char *str)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = BUFFER_SIZE_TOK;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = ft_strtok(str, DELIM_TK);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += BUFFER_SIZE_TOK;
			tokens = ft_reallocdp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = ft_strtok(NULL, DELIM_TK);
		tokens[i] = token;
	}

	return (tokens);
}
