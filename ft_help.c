#include "shell.h"

void ft_exit_help(void)
{
	char *help = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, help, ft_strlen(help));
	help = "Exits the shell with a status of N. If N is ommited, then exit";
	write(STDOUT_FILENO, help, ft_strlen(help));
	help = "status is that of the last command executed\n";
	write(STDOUT_FILENO, help, ft_strlen(help));
}
void ft_env_help(void)
{
	char *help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help, ft_strlen(help));
	help = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, help, ft_strlen(help));

}

void ft_setenv_help(void)
{

	char *help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, help, ft_strlen(help));
	help = "int replace)\n\t";
	write(STDOUT_FILENO, help,ft_strlen(help));
	help = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, help, ft_strlen(help));
}
void ft_gen_help(void)
{
	char *help = "bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help, ft_strlen(help));
	help = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, help, ft_strlen(help));
	help = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, help, ft_strlen(help));
	help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help, ft_strlen(help));
	help = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, help, ft_strlen(help));
	help = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, help, ft_strlen(help));
	help = "unsetenv [variable]\n";
	write(STDOUT_FILENO, help, ft_strlen(help));
}

void ft_unsetenv_help(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, help, ft_strlen(help));
	help = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, help, ft_strlen(help));
}
