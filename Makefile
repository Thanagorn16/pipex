# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: truangsi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 14:40:38 by truangsi          #+#    #+#              #
#    Updated: 2023/02/02 12:21:38 by truangsi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror

NAME = pipex

LIBFT_PATH = libft/

PIPE_SRCS = pipex.c pipex_utils.c

LIBFT_SRCS = ft_strlen.c ft_strjoin_path.c ft_split.c ft_strtrim.c \
			ft_putstr_fd.c ft_putstr_fd.c

SRCS = $(PIPE_SRCS) $(addprefix $(LIBFT_PATH), $(LIBFT_SRCS))

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%o:%c
	gcc $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	gcc $(NAME) $(OBJS)

bonus: all

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all bonus
