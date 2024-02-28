#include "shell.h"

void ft_free_data(sh_data *data)
{
	unsigned int i;

	for (i = 0; data->env_var[i]; i++)
	{
		free(data->env_var[i]);
	}

	free(data->env_var);
	free(data->pid);
}

void ft_set_data(sh_data *data, char **av)
{
	unsigned int i;

	data->arg_v = av;
	data->input = NULL;
	data->args = NULL;
	data->status = 0;
	data->i = 1;

	for (i = 0; environ[i]; i++)
		;

	data->env_var = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		data->env_var[i] = ft_strdup(environ[i]);
	}

	data->env_var[i] = NULL;
	data->pid = ft_itoa(getpid());
}

int main(int ac, char **av)
{
	sh_data data;
	(void) ac;

	signal(SIGINT, ft_sigint_handler);
	ft_set_data(&data, av);
	loop_shell(&data);
	ft_free_data(&data);
	if (data.status < 0)
		return (255);
	return (data.status);
}
