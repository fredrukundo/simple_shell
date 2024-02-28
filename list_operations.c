#include "shell.h"


t_sep_list *add_separator_at_end(t_sep_list **head, char seep)
{
	t_sep_list *new, *temp;

	new = malloc(sizeof(t_sep_list));
	if (new == NULL)
		return (NULL);

	new->sep = seep;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

void free_separator_list(t_sep_list **head)
{
	t_sep_list *temp;
	t_sep_list *cur;

	if (head != NULL)
	{
		cur = *head;
		while ((temp = cur) != NULL)
		{
			cur = cur->next;
			free(temp);
		}
		*head = NULL;
	}
}


t_list_line *add_line_at_end(t_list_line **head, char *line)
{
	t_list_line *new, *temp;

	new = malloc(sizeof(t_list_line));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}


void free_line(t_list_line **head)
{
	t_list_line *temp;
	t_list_line *cur;

	if (head != NULL)
	{
		cur = *head;
		while ((temp = cur) != NULL)
		{
			cur = cur->next;
			free(temp);
		}
		*head = NULL;
	}
}
