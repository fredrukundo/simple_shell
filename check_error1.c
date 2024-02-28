#include "shell.h"

char *ft_env_error(sh_data *data)
{
	int length;
	char *error;
	char *ver_str;
	char *msg;

	ver_str = ft_itoa(data->i);
	msg = ": Unable to add/remove from environment\n";
	length = ft_strlen(data->arg_v[0]) + ft_strlen(ver_str);
	length += ft_strlen(data->args[0]) + ft_strlen(msg) + 4;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}

	ft_strcpy(error, data->arg_v[0]);
	ft_strcat(error, ": ");
	ft_strcat(error, ver_str);
	ft_strcat(error, ": ");
	ft_strcat(error, data->args[0]);
	ft_strcat(error, msg);
	ft_strcat(error, "\0");
	free(ver_str);

	return (error);
}

char *ft_path_error(sh_data *data)
{
	int length;
	char *ver_str;
	char *error;

	ver_str = ft_itoa(data->i);
	length = ft_strlen(data->arg_v[0]) + ft_strlen(ver_str);
	length += ft_strlen(data->args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	ft_strcpy(error, data->arg_v[0]);
	ft_strcat(error, ": ");
	ft_strcat(error, ver_str);
	ft_strcat(error, ": ");
	ft_strcat(error, data->args[0]);
	ft_strcat(error, ": Permission denied\n");
	ft_strcat(error, "\0");
	free(ver_str);
	return (error);
}
int ft_get_error(sh_data *data, int eval)
{
	char *error = NULL;

	switch (eval)
	{
	case -1:
		error = ft_env_error(data);
		break;
	case 126:
		error = ft_path_error(data);
		break;
	case 127:
		error = ft_not_found_error(data);
		break;
	case 2:
		if (ft_strcmp("exit", data->args[0]) == 0)
			error = ft_exit_shell_error(data);
		else if (ft_strcmp("cd", data->args[0]) == 0)
			error = ft_get_cd_error(data);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, ft_strlen(error));
		free(error);
	}

	data->status = eval;
	return (eval);
}
