/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truangsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:14:59 by truangsi          #+#    #+#             */
/*   Updated: 2023/02/03 16:15:01 by truangsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_path(char **envp)
{
	int		i;
	char	**path_env;
	char	*tmp;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
			&& envp[i][2] == 'T' && envp[i][3] == 'H')
			break ;
		i++;
	}
	tmp = ft_strtrim(envp[i], "PATH=");
	path_env = ft_split(tmp, ':');
	free(tmp);
	return (path_env);
}

int	child_process(int fd[], char **av, char **path_env, char **envp)
{
	int		infile;
	char	**cmd;
	char	*str;

	infile = open(av[1], O_RDONLY);
	if (infile < 0)
		is_err(ERR_FILE, av[1]);
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(infile);
	close(fd[0]);
	close(fd[1]);
	cmd = ft_split(av[2], ' ');
	if (access(av[2], F_OK) == 0)
		execve(av[2], cmd, envp);
	if (ft_strncmp(av[2], "/", 1) == 0 && access(av[2], F_OK) == -1)
	{
		str = ft_strdup(cmd[0]);
		free_malloc(path_env);
		free_malloc(cmd);
		is_err(ERR_FILE_CMD, str);
	}
	do_exec(path_env, cmd, envp);
	free_malloc(path_env);
	free_malloc(cmd);
	return (ERR_EXEC);
}

int	parent_process(int fd[], char **av, char **path_env, char **envp)
{
	int		outfile;
	char	**cmd;
	char	*str;
	int		i;

	i = 0;
	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile < 0)
	{
		i = 100000;
		while (i)
			i--;
		is_err(ERR_FILE, av[4]);
	}
	dup2(outfile, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(outfile);
	close(fd[1]);
	close(fd[0]);
	cmd = ft_split(av[3], ' ');
	if (access(av[3], F_OK) == 0)
		execve(av[3], cmd, envp);
	if (ft_strncmp(av[3], "/", 1) == 0 && access(av[3], F_OK) == -1)
	{
		str = ft_strdup(cmd[0]);
		free_malloc(path_env);
		free_malloc(cmd);
		is_err(ERR_FILE_CMD, str);
	}
	do_exec(path_env, cmd, envp);
	free_malloc(path_env);
	free_malloc(cmd);
	return (ERR_EXEC);
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	pipex;

	if (ac != 5)
		is_err(ERR_ARGS, NULL);
	pipex.path_env = find_path(envp);
	if (pipe(pipex.fd) < 0)
		is_err(ERR_PIPE, NULL);
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		is_err(ERR_FORK, NULL);
	if (pipex.pid1 == 0)
	{
		// pipex.child = child_process(pipex.fd, av, pipex.path_env, envp);
		child_process(pipex.fd, av, pipex.path_env, envp);
		// if (pipex.child == 5)
		is_err(ERR_EXEC, av[2]);
	}
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		is_err(ERR_FORK, NULL);
	if (pipex.pid2 == 0)
	{
		// pipex.parent = parent_process(pipex.fd, av, pipex.path_env, envp);
		parent_process(pipex.fd, av, pipex.path_env, envp);
		// if (pipex.parent == 5)
		is_err(ERR_EXEC, av[3]);
	}
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	waitpid(pipex.pid1, &pipex.status, 0);
	waitpid(pipex.pid2, &pipex.status, 0);
	free_malloc(pipex.path_env);
	return (WEXITSTATUS(pipex.status));
}
