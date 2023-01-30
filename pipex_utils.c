#include "pipex.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *) malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (str[i] != '\0')
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strjoin_path(char const *str1, char const *str2) // use to join path with a command
{
	int		i;
	int		a;
	char	*ptr;

	i = 0;
	a = 0;
	if (!str1)
		return (NULL);
	ptr = (char *) malloc((ft_strlen(str1) + ft_strlen(str2) + 2));
	if (!ptr)
		return (NULL);
	while (str1[i] != '\0')
	{
		ptr[i] = str1[i];
		i++;
	}
	while (str2[a] != '\0')
	{
        if (a == 0)
            ptr[i++] = '/';
		ptr[i] = str2[a];
		i++;
		a++;
	}
	ptr[i] = '\0';
	return (ptr);
}