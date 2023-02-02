#include "pipex.h"

// void	ft_putstr(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 		write(1, &str[i++], 1);
// }

void	is_err(int err, char *av)
{
	if (err == 1)
		ft_putstr_fd("Error: there must be 5 arguments", STDERR_FILENO);
	else if (err == 2)
		ft_putstr_fd("Error: failed pipe", STDERR_FILENO);
	else if (err == 3)
		ft_putstr_fd("Error: failed fork", STDERR_FILENO);
	else if (err == 4)
	{
		ft_putstr_fd("zsh: no such file or directory: ", STDERR_FILENO);
		ft_putstr_fd(av, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else if (err == 5)
	{
		ft_putstr_fd("zsh: command not found: ", STDERR_FILENO);
		ft_putstr_fd(av, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		// ft_putstr_fd("Error: cannot execute", STDERR_FILENO);
	}
	exit(0);
}