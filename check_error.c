#include "shell.h"

char *ft_strcat_cd(sh_data *data, char *msg, char *error, char *ver_str)
{
	char *illegal_flag;

	ft_strcpy(error, data->arg_v[0]);
	ft_strcat(error, ": ");
	ft_strcat(error, ver_str);
	ft_strcat(error, ": ");
	ft_strcat(error, data->args[0]);
	ft_strcat(error, msg);
	if (data->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = data->args[1][1];
		illegal_flag[2] = '\0';
		ft_strcat(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		ft_strcat(error, data->args[1]);
	}

	ft_strcat(error, "\n");
	ft_strcat(error, "\0");
	return (error);
}

char *ft_get_cd_error(sh_data *data)
{
	int length, len_id;
	char *error, *ver_str, *msg;

	ver_str = ft_itoa(data->i);
	if (data->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = ft_strlen(data->args[1]);
	}

	length = ft_strlen(data->arg_v[0]) + ft_strlen(data->args[0]);
	length += ft_strlen(ver_str) + ft_strlen(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = ft_strcat_cd(data, msg, error, ver_str);

	free(ver_str);

	return (error);
}

char *ft_not_found_error(sh_data *data)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = ft_itoa(data->i);
	length = ft_strlen(data->arg_v[0]) + ft_strlen(ver_str);
	length += ft_strlen(data->args[0]) + 16;
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
	ft_strcat(error, ": not found\n");
	ft_strcat(error, "\0");
	free(ver_str);
	return (error);
}

char *ft_exit_shell_error(sh_data *data)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = ft_itoa(data->i);
	length = ft_strlen(data->arg_v[0]) + ft_strlen(ver_str);
	length += ft_strlen(data->args[0]) + ft_strlen(data->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	ft_strcpy(error, data->arg_v[0]);
	ft_strcat(error, ": ");
	ft_strcat(error, ver_str);
	ft_strcat(error, ": ");
	ft_strcat(error, data->args[0]);
	ft_strcat(error, ": Illegal number: ");
	ft_strcat(error, data->args[1]);
	ft_strcat(error, "\n\0");
	free(ver_str);

	return (error);
}
