#include "shell.h"

char *infos(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = ft_strlen(name);
	len_value = ft_strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	ft_strcpy(new, name);
	ft_strcat(new, "=");
	ft_strcat(new, value);
	ft_strcat(new, "\0");

	return (new);
}
int env_name_cmp(const char *name_env, const char *name)
{
	int i;

	for (i = 0; name_env[i] != '='; i++)
	{
		if (name_env[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

char *ft_getenv(const char *name, char **envi)
{
	char *ptr_env;
	int i, mov;
	ptr_env = NULL;
	mov = 0;
	for (i = 0; envi[i]; i++)
	{
		mov = env_name_cmp(envi[i], name);
		if (mov)
		{
			ptr_env = envi[i];
			break;
		}
	}

	return (ptr_env + mov);
}

int ft_env(sh_data *data)
{
	int i, j;

	for (i = 0; data->env_var[i]; i++)
	{

		for (j = 0; data->env_var[i][j]; j++)
			;

		write(STDOUT_FILENO, data->env_var[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	data->status = 0;

	return (1);
}
