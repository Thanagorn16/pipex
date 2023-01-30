#ifndef PIPEX
#define PIPEX

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *str);
char	*ft_strtrim(char const *str, char const *set);
char	*ft_strjoin_path(char const *str1, char const *str2);


#endif