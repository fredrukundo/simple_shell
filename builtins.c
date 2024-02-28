#include "shell.h"

int (*ft_get_builtin(char *cmd))(sh_data *data)
{
	t_builtin builtin[] = {
		{ "env", ft_env },
		{ "exit", ft_exit_sh },
		{ "setenv", ft_setenv },
		{ "unsetenv", ft_unsetenv },
		{ "cd", ft_cd_dir },
		{ "help", ft_get_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (ft_strcmp(builtin[i].name, cmd) == 0)
			break;
	}

	return (builtin[i].f);
}
