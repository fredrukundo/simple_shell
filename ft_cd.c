#include "shell.h"

void ft_cd_to(sh_data *data)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = data->args[1];
	if (chdir(dir) == -1)
	{
		ft_get_error(data, 2);
		return;
	}

	cp_pwd = ft_strdup(pwd);
	set_env("OLDPWD", cp_pwd, data);

	cp_dir = ft_strdup(dir);
	set_env("PWD", cp_dir, data);

	free(cp_pwd);
	free(cp_dir);

	data->status = 0;

	chdir(dir);
}

void ft_cd_previous(sh_data *data)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = ft_strdup(pwd);

	p_oldpwd = ft_getenv("OLDPWD", data->env_var);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = ft_strdup(p_oldpwd);

	set_env("OLDPWD", cp_pwd, data);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, data);
	else
		set_env("PWD", cp_oldpwd, data);

	p_pwd = ft_getenv("PWD", data->env_var);

	write(STDOUT_FILENO, p_pwd, ft_strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	data->status = 0;

	chdir(p_pwd);
}

void ft_cd_to_home(sh_data *data)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = ft_strdup(pwd);

	home = ft_getenv("HOME", data->env_var);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, data);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		ft_get_error(data, 2);
		free(p_pwd);
		return;
	}
	set_env("OLDPWD", p_pwd, data);
	set_env("PWD", home, data);
	free(p_pwd);
	data->status = 0;
}
