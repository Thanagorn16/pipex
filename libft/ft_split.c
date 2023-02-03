/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truangsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:06:41 by truangsi          #+#    #+#             */
/*   Updated: 2023/02/03 16:06:43 by truangsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_malloc(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	**get_mal(char const *s, char c)
{
	int		slot;
	int		i;
	char	**arr;

	i = 1;
	slot = 0;
	if (s[0] != '\0')
	{
		while (s[i] && ft_strlen(s) != 0)
		{
			if (s[0] != c && i == 1)
				slot++;
			if (s[i - 1] == c && s[i] != c)
				slot++;
			i++;
		}
		slot++;
	}
	else
		slot = 1;
	arr = (char **) malloc(slot * sizeof(char *));
	if (!arr)
		return (NULL);
	return (arr);
}

char	**insert(char const *s, char c, int slot, char **arr)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (i < slot)
	{
		while (s[count] == c)
			count++;
		while (s[count] != c && s[count] != '\0')
		{
			arr[i][j] = s[count];
			j++;
			count++;
		}
		arr[i][j] = '\0';
		j = 0;
		i++;
	}
	arr[slot] = NULL;
	return (arr);
}

char	**allocate(char const *s, char c, char **arr)
{
	t_split	split;

	split.i = 0;
	split.count = 0;
	split.slot = 0;
	while (split.i < ft_strlen(s))
	{
		while (s[split.i] != c && s[split.i] != '\0')
		{
			split.i++;
			split.count++;
		}
		if (split.count > 0)
		{
			arr[split.slot] = (char *) malloc(split.count + 1);
			if (!arr[split.slot])
				return (free_malloc(arr), NULL);
			split.slot++;
			split.count = 0;
		}
		split.i++;
	}
	arr = insert(s, c, split.slot, arr);
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;

	if (!s)
		return (NULL);
	arr = get_mal(s, c);
	if (!arr)
		return (NULL);
	arr = allocate(s, c, arr);
	return (arr);
}
