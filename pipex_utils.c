/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truangsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:19:00 by truangsi          #+#    #+#             */
/*   Updated: 2023/02/03 16:19:02 by truangsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	zhs_err(int err, char *av)
{
	if (err == 4)
	{
		ft_putstr_fd("zsh: no such file or directory: ", STDERR_FILENO);
		ft_putstr_fd(av, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		errno = 1;
		if (av[0] == '/')
			errno = 127;
	}
	else if (err == 5)
	{
		ft_putstr_fd("zsh: command not found: ", STDERR_FILENO);
		ft_putstr_fd(av, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		errno = 127;
	}
	exit (errno);
}

void	is_err(int err, char *av)
{
	if (err == 1)
	{
		ft_putstr_fd("Error: there must be 5 arguments\n", STDERR_FILENO);
		errno = 1;
	}
	else if (err == 2)
		ft_putstr_fd("Error: failed pipe\n", STDERR_FILENO);
	else if (err == 3)
		ft_putstr_fd("Error: failed fork\n", STDERR_FILENO);
	else if (err == 4)
		zhs_err(err, av);
	else if (err == 5)
		zhs_err(err, av);
	else if (err == 6)
	{
		ft_putstr_fd("zsh: no such file or directory: ", STDERR_FILENO);
		ft_putstr_fd(av, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		errno = 1;
		if (av[0] == '/')
			errno = 127;
		free(av);
	}
	exit(errno);
}

void	do_exec(char **path_env, char **cmd, char **envp)
{
	t_pipe	pipex;

	pipex.i = 0;
	pipex.path_cmd = NULL;
	while (path_env[pipex.i])
	{
		pipex.old_path = path_env[pipex.i];
		path_env[pipex.i++] = ft_strjoin_path(path_env[pipex.i], cmd[0]);
		free(pipex.old_path);
	}
	pipex.i = 0;
	while (path_env[pipex.i])
	{
		if (access(path_env[pipex.i], F_OK) == -1)
			pipex.i++;
		else
		{
			pipex.path_cmd = ft_strdup(path_env[pipex.i]);
			free_malloc(path_env);
			break ;
		}
	}
	execve(pipex.path_cmd, cmd, envp);
	free(pipex.path_cmd);
}
