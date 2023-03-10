/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truangsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:07:15 by truangsi          #+#    #+#             */
/*   Updated: 2023/02/03 16:07:16 by truangsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;

	i = 1;
	s1 = (unsigned char *) str1;
	s2 = (unsigned char *) str2;
	while (i <= n)
	{
		if (s1[i - 1] < s2[i - 1] || s1[i - 1] > s2[i - 1])
			return (s1[i - 1] - s2[i - 1]);
		if (s1[i] == '\0' && s2[i] == '\0')
			return (s1[i - 1] - s2[i - 1]);
		i++;
	}
	return (0);
}
