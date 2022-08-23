# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/01 11:05:39 by gabdoush          #+#    #+#              #
#    Updated: 2022/06/29 18:27:37 by gabdoush         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef VERPOSE
.SILENT:
endif

NAME = libft.a

FILES =  ft_atoi\
	 ft_isalnum\
	 ft_isalpha\
	 ft_isascii\
	 ft_isdigit\
	 ft_isprint\
	 ft_itoa\
	 ft_tolower\
	 ft_toupper\
	 ft_bzero\
	 ft_calloc\
	 ft_memcmp\
	 ft_memset\
	 ft_memcpy\
	 ft_memmove\
	 ft_memchr\
	 ft_split\
	 ft_strchr\
	 ft_strlen\
	 ft_strdup\
	 ft_strlcat\
	 ft_strjoin\
	 ft_strtrim\
	 ft_strlcpy\
	 ft_strncmp\
	 ft_strnstr\
	 ft_strrchr\
	 ft_putchar_fd\
	 ft_putstr_fd\
	 ft_putendl_fd\
	 ft_putnbr_fd\
	 ft_strmapi\
	 ft_substr\
	 ft_striteri\
	 ft_putstrs_fd\
	 ft_strcmp\
	 ft_strcpy\
	 ft_strjoin_mult


OBJECTS =	$(FILES:.c=.o)

HEADERS = libft.h 

FLAGS = -Wall -Werror -Wextra

CC = gcc -c

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rc libft.a $(OBJECTS)

clean:
	/bin/rm -f $(OBJECTS)

fclean: clean
	/bin/rm -f  $(NAME)

re: fclean all

.PHONY:	all clean fclean re