#include "shell.h"

int ft_get_help(sh_data *data)
{

	if (data->args[1] == 0)
		ft_gen_help();
	else if (ft_strcmp(data->args[1], "setenv") == 0)
		ft_setenv_help();
	else if (ft_strcmp(data->args[1], "env") == 0)
		ft_env_help();
	else if (ft_strcmp(data->args[1], "unsetenv") == 0)
		ft_unsetenv_help();
	else if (ft_strcmp(data->args[1], "help") == 0)
		ft_help();
	else if (ft_strcmp(data->args[1], "exit") == 0)
		ft_exit_help();
	else if (ft_strcmp(data->args[1], "cd") == 0)
		ft_cd_help();
	else if (ft_strcmp(data->args[1], "alias") == 0)
		ft_alias_help();
	else
		write(STDERR_FILENO, data->args[0],
		      ft_strlen(data->args[0]));

	data->status = 0;
	return (1);
}

void ft_help(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, ft_strlen(help));
	help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, help, ft_strlen(help));
	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, ft_strlen(help));
}

void ft_alias_help(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, ft_strlen(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, ft_strlen(help));
}

void ft_cd_help(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, ft_strlen(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, ft_strlen(help));
}
