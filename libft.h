/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 14:51:33 by smilch            #+#    #+#             */
/*   Updated: 2026/06/22 14:51:40 by smilch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>

// t_list def
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

// macros for lookup variables
# define FT_A	(1 << 0)
# define FT_D	(1 << 1)
# define FT_P	(1 << 2)
# define FT_S	(1 << 3)
# define CTYPE_NUM_CHARS	256

// lookup table for ctype functions - optimized for less calculation
extern const unsigned char	g_lup[1 + CTYPE_NUM_CHARS];

// macros for ctype functions
# define ft_isalpha(c)	((g_lup[(unsigned char)(c + 1)] & FT_A) != 0)
# define ft_isdigit(c)	((g_lup[(unsigned char)(c + 1)] & FT_D) != 0)
# define ft_isprint(c)	((g_lup[(unsigned char)(c + 1)] & FT_P) != 0)
# define ft_isspace(c)	((g_lup[(unsigned char)(c + 1)] & FT_S) != 0)
# define ft_isalnum(c)	((g_lup[(unsigned char)(c + 1)] & (FT_A | FT_D)) != 0)
# define ft_isascii(c)  (((c) & ~0x7F) == 0)

// part one - libc
int		ft_atoi(const char *str);
void	ft_bzero(void *to, size_t count);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *s1, const void *s2, size_t n);
void	*ft_memmove(void *s1, const void *s2, size_t n);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strdup(const char *str);
size_t	ft_strlcat(char *dest, const char *src, size_t dsize);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *str, const char *to_find, size_t slen);
char	*ft_strrchr(const char *p, int ch);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_strchr(const char *p, int ch);

// part two
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// linked list functions
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
#endif
