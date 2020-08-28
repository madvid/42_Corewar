/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 13:11:02 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/28 13:01:58 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*
** Include of extra header files
*/
# include <unistd.h>
# include <string.h>

/*
** Definition of some constants
*/
# ifndef LONG_MAX
#  define LONG_MAX 9223372036854775807
# endif
# ifndef INTEGER_MAX
#  define INTEGER_MAX 2147483647
# endif
# define BASE "0123456789abcdef"

/*
** Definition of structures
*/
typedef struct		s_list
{
	void			*cnt;
	struct s_list	*next;
}					t_list;

/*
** Fonctions de la partie oligatoire
*/
void				*ft_memset(void *str, int c, size_t len);
void				ft_bzero(void *str, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t len);
void				*ft_memccpy(void *dst, const void *src, int c, size_t len);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *str, int c, size_t len);
int					ft_memcmp(const void *s1, const void *s2, size_t len);
size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *s);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
/*
** Fonctions de la partie supplementaire
*/
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char s, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
/*
** Fonctions de la partie bonus
*/
t_list				*ft_lstnew(void const *content);
void				ft_lstdelone(t_list **alst, void (*del)(void*));
void				ft_lstdel(t_list **alst, void (*del)(void *));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					ft_isupper(int c);
int					ft_islower(int c);
size_t				ft_power(unsigned int n, int pow);
void				ft_eraser(void *tab, size_t index);
char				*ft_strjoin_1n(char **s1, char const *s2);
char				*ft_strdup_1n(const char *s);
char				*ft_strjoin_1sp(char const *s1, char const *s2);
char				*ft_strdup_1sp(const char *s);
char				*ft_strdup_p(const char *s);
char				*ft_strtrunc_x(char *s, size_t x);
int					ft_strdupfree(char **dest, char **src);

/*
** Fonctions ajoutées post projet libft
*/
unsigned long long	ft_atoull(const char *str);
int					ft_is_positive_int(char *str);
void				ft_strtolower(char *str);
char				*ft_strnew_c(size_t size, char c);
char				*ft_strreset(char *s1, char *s2);
int					ft_str_isnumber(char *number);
void				ft_strtabldel(char ***tab);
char				*ft_itoa_base(int nb, char* strbase, int base);
void				ft_print_binary(int nb);
void				ft_lstaddend(t_list **alst, t_list *add);
void				ft_lst_fdel(void *link, size_t link_size);
int					ft_lst_len(t_list *lst);
int					ft_lst_issort(t_list *lst, int (*ft_lst_order)(t_list*, t_list*));
t_list				*ft_lst_swap(t_list * link1, t_list *link2);
void				ft_1d_int_tabledel(int **tab, int nb_elem);
void				ft_1d_int_table_set(int *table, int nb, size_t ini, size_t width);
int					*ft_1d_int_table(int nb_elem);

#endif
