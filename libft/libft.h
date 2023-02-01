#ifndef LIBFT
#define LIBFT

#include <unistd.h>
#include <stdlib.h>

size_t	ft_strlen(const char *str);
void	free_malloc(char **arr);
char	**ft_split(char const *s, char c);
char	*ft_strtrim(char const *str, char const *set);
char	*ft_strdup(const char *str);
char	*ft_strjoin_path(char const *str1, char const *str2);
void	ft_putstr_fd(char *s, int fd);

#endif