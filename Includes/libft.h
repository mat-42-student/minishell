/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:56:20 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/06/01 10:58:25 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# define RED "\033[31;1m"
# define GREEN "\033[32;1m"
# define YELLOW	"\033[33;1m"
# define CYAN	"\033[36;1m"

# define RESET "\033[0m"

typedef struct s_list	t_list;
typedef struct s_2list	t_2list;

struct s_list
{
	void	*content;
	t_list	*next;
};

struct s_2list
{
	int		val;
	int		rank;
	t_2list	*next;
	t_2list	*prev;
};

int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
int			ft_isint(long n);
int			ft_isspace(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
// ft_is_in : return the position of c in s, or -1 if c is not present
int			ft_is_in(const char c, const char *s);
int			ft_where_is(char c, char *str);

char		**ft_lst_to_strtab(t_list *lst);
char		**ft_lstsplit(char *str, char sep);
char		**ft_split(char const *s, char c);
char		**ft_split_by_lst(char *str, char sep);
char		**ft_quotesplit(char *str, char sep);
size_t		ft_sstrlen(const char *s);
char		*ft_strchr(const char *s, int c);
int			ft_strdelchar(char **str_ptr, int i);
int			ft_strdelfrom(char *str, int i);
int			ft_strdelnfrom(char **str, int i, int nb_del);
char		*ft_strdup(const char *s1);
int			ft_strequal(char *str1, char *str2);
int			ft_strisdigit(const char *str);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strfjoin(char *s1, char *s2);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_strlastof(char	*str, char c);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
char		*ft_strmanyjoin(char *str, ...);
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strrchr(const char *s, int c);
int			ft_strresize(char **str_ptr, int val);
char		*ft_strtrim(char const *s1, char const *set);
int			ft_strtrunc(char **str, int start, int len);
int			ft_strinsert(char **str1, char *str2, int pos);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_substr(char const *s, unsigned int start, size_t len);

void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		ft_freenull(void **ptr);
void		ft_freestr(char **ptr);
void		ft_freetab(char **s);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);

long long	ft_atoi(const char *str);
char		*ft_itoa(int n);

int			ft_printf(const char *base, ...);
void		ft_printstrtab(char **str_tab, char *titre);
char		*get_next_line(int fd);

void		ft_putchar_fd(char c, int fd);
// ft_putendl_fd : write s then write "\n" on the specified fd
void		ft_putendl_fd(char *s, int fd);
int			ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

int			ft_abs(int a);
int			ft_inc_value(int a, int b);
size_t		ft_max(size_t a, size_t b);
size_t		ft_min(size_t a, size_t b);
int			ft_sign(int n);

void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);

t_2list		*ft_2lstnew(int value, int rank);
void		ft_2lstadd_back(t_2list **lst, t_2list *new);
void		ft_2lstadd_front(t_2list **a, t_2list *new);
void		ft_2lstdelone(t_2list **lst);
void		*ft_2lstclear(t_2list **a);
t_2list		*ft_2lstlast(t_2list *lst);
int			ft_2lstsize(t_2list *lst);

#endif
