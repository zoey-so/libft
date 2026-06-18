#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
//# include <ctype.h>



# define FT_A	(1 << 0)
# define FT_D	(2 << 0)
# define FT_P	(3 << 0)
# define FT_S	(4 << 0)
# define CTYPE_NUM_CHARS	256
extern const unsigned char	g_lup[1 + CTYPE_NUM_CHARS];
# define ft_isalpha(c)	((g_lup[(unsigned char)(c + 1)] & FT_A) != 0)
# define ft_isdigit(c)	((g_lup[(unsigned char)(c + 1)] & FT_D) != 0)
# define ft_isprint(c)	((g_lup[(unsigned char)(c + 1)] & FT_P) != 0)
# define ft_isspace(c)	((g_lup[(unsigned char)(c + 1)] & FT_S) != 0)
# define ft_isalnum(c)	((g_lup[(unsigned char)(c + 1)] & (FT_A | FT_D)) != 0)
# define ft_isascii(c)  (((c) & ~0x7F) == 0)

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
#endif