/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truangsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:15:15 by truangsi          #+#    #+#             */
/*   Updated: 2023/02/03 16:15:17 by truangsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <sys/errno.h>
# include <sys/types.h>

# define ERR_ARGS 1
# define ERR_PIPE 2
# define ERR_FORK 3
# define ERR_FILE 4
# define ERR_EXEC 5
# define ERR_FILE_CMD 6

typedef struct s_pipe
{
	char	**path_env;
	char	**cmd;
	char	*str;
	char	*old_path;
	char	*path_cmd;
	int		i;
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		child;
	int		parent;
	int		status;
	int		infile;
	int		outfile;
}	t_pipe;

char	**find_path(char **envp);
int		child_process_a(int fd[], char **av, char **path_env, char **envp);
void	fork_child_b(t_pipe pipex, char **av, char **envp, char **err_cmd);
int		child_process_b(int fd[], char **av, char **path_env, char **envp);
void	zhs_err(int err, char *av);
void	is_err(int err, char *av);
void	do_exec(char **path_env, char **cmd, char **envp);

#endif
