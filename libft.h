#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <ctype.h>

extern const unsigned char	g_lup[1 + CTYPE_NUM_CHARS];

# define FT_A	(1 << 0);
# define FT_D	(2 << 0);
# define FT_P	(3 << 0);
# define FT_S	(4 << 0);
# define ft_isalpha(c)	((g_lup[(unsigned char)(c + 1)] & FT_A) != 0)
# define ft_isdigit(c)	((g_lup[(unsigned char)(c + 1)] & FT_D) != 0)
# define ft_isprint(c)	((g_lup[(unsigned char)(c + 1)] & FT_P) != 0)
# define ft_isspace(c)	((g_lup[(unsigned char)(c + 1)] & FT_S) != 0)
# define ft_isspace(c)	((g_lup[(unsigned char)(c + 1)] & (FT_A | FT_D)) != 0)
# define ft_isascii(c)  (((c) & ~0x7F) == 0)

size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memcpy(void *s1, const void *s2, size_t n);
#endif