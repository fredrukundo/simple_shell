#include "shell.h"

int ft_exit_sh(sh_data *data)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (data->args[1] != NULL)
	{
		ustatus = ft_atoi(data->args[1]);
		is_digit = ft_isdigit(data->args[1]);
		str_len = ft_strlen(data->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			ft_get_error(data, 2);
			data->status = 2;
			return (1);
		}
		data->status = (ustatus % 256);
	}
	return (0);
}

void ft_cd_dot(sh_data *data)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = ft_strdup(pwd);
	set_env("OLDPWD", cp_pwd, data);
	dir = data->args[1];
	if (ft_strcmp(".", dir) == 0)
	{
		set_env("PWD", cp_pwd, data);
		free(cp_pwd);
		return;
	}
	if (ft_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	ft_rev_str(cp_strtok_pwd);
	cp_strtok_pwd = ft_strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = ft_strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			ft_rev_str(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, data);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", data);
	}
	data->status = 0;
	free(cp_pwd);
}

int ft_cd_dir(sh_data *data)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = data->args[1];

	if (dir != NULL)
	{
		ishome = ft_strcmp("$HOME", dir);
		ishome2 = ft_strcmp("~", dir);
		isddash = ft_strcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		ft_cd_to_home(data);
		return (1);
	}

	if (ft_strcmp("-", dir) == 0)
	{
		ft_cd_previous(data);
		return (1);
	}

	if (ft_strcmp(".", dir) == 0 || ft_strcmp("..", dir) == 0)
	{
		ft_cd_dot(data);
		return (1);
	}

	ft_cd_to(data);

	return (1);
}
