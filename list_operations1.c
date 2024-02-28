#include "shell.h"


t_list_vars *add_var_end(t_list_vars **head, int l_var, char *var, int l_val)
{
	t_list_vars *new, *temp;

	new = malloc(sizeof(t_list_vars));
	if (new == NULL)
		return (NULL);

	new->len = l_var;
	new->val = var;
	new->val_len = l_val;

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

void free_var(t_list_vars **head)
{
	t_list_vars *temp;
	t_list_vars *cur;

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
