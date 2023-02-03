/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truangsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:06:58 by truangsi          #+#    #+#             */
/*   Updated: 2023/02/03 16:07:00 by truangsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
int		ft_strncmp(const char *str1, const char *str2, size_t n);

#endif
