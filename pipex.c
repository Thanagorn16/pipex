#include "pipex.h"

char	**find_path(char **envp, char **av)
{
	int	i;
	char	*path;
	char	**path_env;
	char	**cmd;

	i = 0;
	while (envp[i]) // get the path index
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
			&& envp[i][2] == 'T' && envp[i][3] == 'H')
			break;
		i++;
	}
	path_env = ft_split(envp[i], ':'); // split them with :
	path_env[0] = ft_strtrim(path_env[0], "PATH="); // trim PATH=
	return (path_env); // return path without '/ to command'
}

int	child_process(int fd[], char **av, char **path_env, char **envp)
{
	int		infile;
	char	**cmd;
	int		i;

	infile = open(av[1], O_RDONLY);
	if (infile < 0)
		is_err(ERR_FILE);
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(infile);
	close(fd[0]);
	close(fd[1]);
	cmd = ft_split(av[2], ' '); // split command (av[2]) from argument
	i = 0;
	while (path_env[i]) // joint path with '/'
	{
		path_env[i] = ft_strjoin_path(path_env[i], cmd[0]);
		i++;
	}
	i = 0;
	while (path_env[i])
	{
		if (access(path_env[i], F_OK) == -1)
			i++;
		else // if the file exist, break
			break ;
	}
	if (execve(path_env[i], cmd, envp) == -1)
	{
		free_malloc(path_env);
		free_malloc(cmd);
	}
	return (ERR_EXEC); // fail to execute
}

int	parent_process(int fd[], char **av, char **path_env, char **envp)
{
	int	outfile;
	int	i;
	char	**cmd;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile < 0)
		is_err(ERR_FILE);
	dup2(outfile, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(outfile);
	close(fd[1]);
	close(fd[0]);
	cmd = ft_split(av[3], ' ');
	i = 0;
	while (path_env[i])
	{
		path_env[i] = ft_strjoin_path(path_env[i], cmd[0]);
		i++;
	}
	i = 0;
	while (path_env[i])
	{
		if (access(path_env[i], F_OK) == -1)
			i++;
		else
			break ;
	}
	if (execve(path_env[i], cmd, envp) == -1)
	{
		free_malloc(path_env);
		free_malloc(cmd);
	}
	return (ERR_EXEC); // fail to execute
}

int	main(int ac, char **av, char **envp)
{
	char	**path_env;
	char	**cmd;
	int		fd[2]; // pipe
	int		pid;
	int		child;
	int		parent;

	if (ac != 5)
		is_err(ERR_ARGS);
	path_env = find_path(envp, av);
	if (pipe(fd) < 0)
		is_err(ERR_PIPE);
	pid = fork();
	if (pid < 0)
		is_err(ERR_FORK);
	if (pid == 0)
	{
		child = child_process(fd, av, path_env, envp);
		if (child == 5)
			is_err(ERR_EXEC);
	}
	else
	{
		wait(NULL);
		parent = parent_process(fd, av, path_env, envp);
		if (parent == 5)
			is_err(ERR_EXEC);
	}
	// wait(NULL);
}