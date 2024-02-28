#include "shell.h"

void valid_env(t_list_vars **h, char *in, sh_data *data)
{
	int row, chr, j, lval;
	char **t_envr;

	t_envr = data->env_var;
	for (row = 0; t_envr[row]; row++)
	{
		for (j = 1, chr = 0; t_envr[row][chr]; chr++)
		{
			if (t_envr[row][chr] == '=')
			{
				lval = ft_strlen(t_envr[row] + chr + 1);
				add_var_end(h, j, t_envr[row] + chr + 1, lval);
				return;
			}

			if (in[j] == t_envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	add_var_end(h, j, NULL, 0);
}


int valid_vars(t_list_vars **h, char *in, char *st, sh_data *data)
{
	int i, lst, lpd;

	lst = ft_strlen(st);
	lpd = ft_strlen(data->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_var_end(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				add_var_end(h, 2, data->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				add_var_end(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_var_end(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_var_end(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_var_end(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_var_end(h, 0, NULL, 0);
			else
				valid_env(h, in + i, data);
		}
	}

	return (i);
}

char *rep_inputs(t_list_vars **head, char *input, char *new_input, int nlen)
{
	t_list_vars *indx;
	int i, j, k;

	indx = *head;
	for (j = i = 0; i < nlen; i++)
	{
		if (input[j] == '$')
		{
			if (!(indx->len) && !(indx->val_len))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (indx->len && !(indx->val_len))
			{
				for (k = 0; k < indx->len; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->val_len; k++)
				{
					new_input[i] = indx->val[k];
					i++;
				}
				j += (indx->len);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

char *replace_str_var(char *input, sh_data *datash)
{
	t_list_vars *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = ft_itoa(datash->status);
	head = NULL;

	olen = valid_vars(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->val_len - indx->len);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = rep_inputs(&head, input, new_input, nlen);

	free(input);
	free(status);
	free_var(&head);

	return (new_input);
}
