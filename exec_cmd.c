#include "shell.h"

int check_is_curr_dir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}


char *which_cmd(char *cmd, char **envi)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = ft_getenv("PATH", envi);
	if (path)
	{
		ptr_path = ft_strdup(path);
		len_cmd = ft_strlen(cmd);
		token_path = ft_strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (check_is_curr_dir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = ft_strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			ft_strcpy(dir, token_path);
			ft_strcat(dir, "/");
			ft_strcat(dir, cmd);
			ft_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = ft_strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}


int cmd_check_error(char *dir, sh_data *datash)
{
	if (dir == NULL)
	{
		ft_get_error(datash, 127);
		return (1);
	}

	if (ft_strcmp(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			ft_get_error(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			ft_get_error(datash, 126);
			return (1);
		}
	}

	return (0);
}
