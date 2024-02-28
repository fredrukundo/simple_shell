#include "shell.h"

void set_env(char *var_name, char *var_value, sh_data *data)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; data->env_var[i]; i++)
	{
		var_env = ft_strdup(data->env_var[i]);
		name_env = ft_strtok(var_env, "=");
		if (ft_strcmp(name_env, var_name) == 0)
		{
			free(data->env_var[i]);
			data->env_var[i] = infos(name_env, var_value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	data->env_var = ft_reallocdp(data->env_var, i, sizeof(char *) * (i + 2));
	data->env_var[i] = infos(var_name, var_value);
	data->env_var[i + 1] = NULL;
}

int ft_setenv(sh_data *data)
{

	if (data->args[1] == NULL || data->args[2] == NULL)
	{
		ft_get_error(data, -1);
		return (1);
	}

	set_env(data->args[1], data->args[2], data);

	return (1);
}

int ft_unsetenv(sh_data *data)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (data->args[1] == NULL)
	{
		ft_get_error(data, -1);
		return (1);
	}
	k = -1;
	for (i = 0; data->env_var[i]; i++)
	{
		var_env = ft_strdup(data->env_var[i]);
		name_env = ft_strtok(var_env, "=");
		if (ft_strcmp(name_env, data->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		ft_get_error(data, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; data->env_var[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = data->env_var[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(data->env_var[k]);
	free(data->env_var);
	data->env_var = realloc_environ;
	return (1);
}
