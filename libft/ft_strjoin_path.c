/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truangsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:06:21 by truangsi          #+#    #+#             */
/*   Updated: 2023/02/03 16:06:22 by truangsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*do_join(char const *str1, char const *str2, char *ptr)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
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

char	*ft_strjoin_path(char const *str1, char const *str2)
{
	char	*ptr;

	if (!str1)
		return (NULL);
	ptr = (char *) malloc((ft_strlen(str1) + ft_strlen(str2) + 2));
	if (!ptr)
		return (NULL);
	ptr = do_join(str1, str2, ptr);
	return (ptr);
}
