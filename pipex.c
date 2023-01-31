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

	infile = open("infile", O_RDONLY);
	if (infile < 0)
		return (3);
	dup2(infile, STDIN_FILENO);
	// dup2(fd[1], stdout);
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
		exit(3);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char	**path_env;
	// char	*test_path = "/bin/ls"; //* this is the correct path for "ls". The others are fault.
	// char    *test_path2 = "/bin/ls";
	char	**cmd;
	// char	*args[] = {"ls", "-l", NULL};
	int		fd[2]; // pipe
	int		pid;
	int		infile;

	path_env = find_path(envp, av);
	if (pipe(fd) < 0)
		return (1);
	pid = fork();
	if (pid < 0)
		return (2);
	if (pid == 0)
		child_process(fd, av, path_env, envp);
	// else
	// {
	// 	printf("\nparent\n");
	// }
	// printf("%s\n", path_env[0]);
}