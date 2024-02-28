#include "shell.h"

int check_is_executable(sh_data *data)
{
	struct stat st;
	int i;
	char *input;

	input = data->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	ft_get_error(data, 127);
	return (-1);
}
int execute_line(sh_data *data)
{
	int (*builtin)(sh_data *data);

	if (data->args[0] == NULL)
		return (1);

	builtin = ft_get_builtin(data->args[0]);

	if (builtin != NULL)
		return (builtin(data));

	return (exec_command(data));
}
int exec_command(sh_data *data)
{
	pid_t pd;
	pid_t wpd;
	int state = 0;
	int exec;
	char *dir;
	(void) wpd;

	exec = check_is_executable(data);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = which_cmd(data->args[0], data->env_var);
		if (cmd_check_error(dir, data) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = which_cmd(data->args[0], data->env_var);
		else
			dir = data->args[0];
		execve(dir + exec, data->args, data->env_var);
	}
	else if (pd < 0)
	{
		perror(data->arg_v[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	data->status = state / 256;
	return (1);
}
