#include "shell.h"

void ft_sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\nmy_shell($) ", 12);
}
