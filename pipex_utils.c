#include "pipex.h"

void	is_err(int err)
{
	if (err == 1)
		ft_putstr_fd("Error: there must be 5 arguments", STDERR_FILENO);
	else if (err == 2)
		ft_putstr_fd("Error: failed pipe", STDERR_FILENO);
	else if (err == 3)
		ft_putstr_fd("Error: failed fork", STDERR_FILENO);
	else if (err == 4)
		perror("Error");
	else if (err == 5)
		ft_putstr_fd("Error: cannot execute", STDERR_FILENO);
	exit(0);
}