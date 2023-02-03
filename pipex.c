#include "pipex.h"

char	**find_path(char **envp)
{
	int	i;
	char	**path_env;

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
	char	*str;
	int		i;

	infile = open(av[1], O_RDONLY);
	if (infile < 0)
		is_err(ERR_FILE, av[1]);
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(infile);
	close(fd[0]);
	close(fd[1]);
	cmd = ft_split(av[2], ' '); // split command (av[2]) from argument
	if (access(av[2], F_OK) == 0)
		execve(av[2], cmd, envp);
	if (ft_strncmp(av[2], "/", 1) == 0 && access(av[2], F_OK) == -1)
	{
		str = ft_strdup(cmd[0]);
		free_malloc(path_env);
		free_malloc(cmd);
		// is_err(ERR_FILE, av[2]);
		is_err(ERR_FILE, str);
	}
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
	char	*str;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile < 0)
		is_err(ERR_FILE, av[4]);
	dup2(outfile, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(outfile);
	close(fd[1]);
	close(fd[0]);
	cmd = ft_split(av[3], ' '); // cmd = {cmd1, cmd2, NULL}
	if (access(av[3], F_OK) == 0)
		execve(av[3], cmd, envp);
	if (ft_strncmp(av[3], "/", 1) == 0 && access(av[3], F_OK) == -1)
	{
		str = ft_strdup(cmd[0]);
		free_malloc(path_env);
		free_malloc(cmd);
		// is_err(ERR_FILE, av[3]);
		is_err(ERR_FILE, str);
	}
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
	int		fd[2]; // pipe
	int		pid;
	int		child;
	int		parent;

	if (ac != 5)
		is_err(ERR_ARGS, NULL);
	path_env = find_path(envp);
	if (pipe(fd) < 0)
		is_err(ERR_PIPE, NULL);
	pid = fork();
	if (pid < 0)
		is_err(ERR_FORK, NULL);
	if (pid == 0)
	{
		child = child_process(fd, av, path_env, envp);
		if (child == 5)
			is_err(ERR_EXEC, av[2]);
	}
	else
	{
		// wait(NULL);
		parent = parent_process(fd, av, path_env, envp);
		if (parent == 5)
			is_err(ERR_EXEC, av[3]);
	}
	wait(NULL); // wait here as there's some case that child process need the data from parent process
}