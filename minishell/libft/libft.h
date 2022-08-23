/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 11:05:29 by gabdoush          #+#    #+#             */
/*   Updated: 2022/08/15 03:59:44 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>

int				ft_atoi(const char *str);
int				ft_isalnum(int n);
int				ft_isalpha(int n);
int				ft_isascii(int n);
int				ft_isdigit(int n);
int				ft_isprint(int n);
int				ft_tolower(int n);
int				ft_toupper(int n);
void			ft_bzero(void *dest, size_t len);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_memcmp(const void *s1, const void *s2, size_t len);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *dest, int c, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *b, int c, size_t len);
char			*ft_strchr(const char *s, int c);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
int				ft_strncmp(const char *s1, const char *s2, size_t len);
char			*ft_strnstr(const char *s1, const char *s2, size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
int				ft_putstrs_fd(char *before, char *str, char *after, int fd);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strjoin_mult(int str_num, ...);

#endif