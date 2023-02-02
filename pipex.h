#ifndef PIPEX
#define PIPEX

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"
#include <sys/errno.h>

#define	ERR_ARGS 1
#define	ERR_PIPE 2
#define	ERR_FORK 3
#define	ERR_FILE 4
#define	ERR_EXEC 5


char	**find_path(char **envp);
int		child_process(int fd[], char **av, char **path_env, char **envp);
int		parent_process(int fd[], char **av, char **path_env, char **envp);
void	is_err(int err, char *av);

#endif