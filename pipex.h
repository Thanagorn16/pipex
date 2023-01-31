#ifndef PIPEX
#define PIPEX

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"

// size_t	ft_strlen(const char *str);
// char	**ft_split(char const *s, char c);
// char	*ft_strdup(const char *str);
// char	*ft_strtrim(char const *str, char const *set);
// char	*ft_strjoin_path(char const *str1, char const *str2);

char	**find_path(char **envp, char **av);
int		child_process(int fd[], char **av, char **path_env, char **envp);

#endif