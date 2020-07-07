/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 15:20:31 by armajchr          #+#    #+#             */
/*   Updated: 2019/10/08 13:32:18 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <limits.h>
# include <float.h>
# include <string.h>
# include <inttypes.h>
# include <math.h>

# define EOC		"\033[0m"
# define HIGHLIGHT	"\033[1m"
# define UNDERLINE	"\033[4m"
# define BLINK		"\033[5m"
# define BLACK		"\033[30m"
# define RED		"\033[31m"
# define GREEN 		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define PURPLE		"\033[35m"
# define CYAN		"\033[36m"
# define WHITE		"\033[37m"

# define F_SHARP	(1 << 0)
# define F_SPACE	(1 << 1)
# define F_PLUS		(1 << 2)
# define F_ZERO		(1 << 3)
# define F_MINUS	(1 << 4)
# define F_LONG		(1 << 5)
# define F_LONG2	(1 << 6)
# define F_SHORT	(1 << 7)
# define F_SHORT2	(1 << 8)
# define F_POINT	(1 << 9)
# define F_STAR		(1 << 10)
# define F_INT		(1 << 11)
# define F_SIZET	(1 << 12)
# define F_FLOAT	(1 << 13)

# define BUFF_SIZE	30

char				g_buff[BUFF_SIZE];
int					g_i;

typedef struct		s_print
{
	int		n;
	int		f;
	int		count;
	int		trash;
	int		len;
	int		diff;
	va_list	ap;
	char	*format;
	int		widht;
	int		precision;
	int		prec;
	char	type;
	int		check;
	int		ipart;
	float	fpart;
}					t_print;

union				u_decimal{
	float		f;
	uint32_t	u;
};

typedef void	(*t_tab)(t_print *);
t_tab				g_tab[256];

int					ft_printf(const char *restrict format, ...);
long long			ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strnew(size_t size);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strjoin(char const *s1, char const *s2);
int					ft_floatlen(char *s);
/*
**---------------------------------------------------------
*/
void				init_buffer(void);
void				init_tab(void);
void				display_buffer(t_print *p);
void				fill_buffer(char c, t_print *p);
/*
**---------------------------------------------------------
*/
void				parsing_flag(t_print *p);
void				parsing_widht(t_print *p);
void				parsing_precision(t_print *p, int i);
void				parsing_size(t_print *p);
void				parsing_type(t_print *p);
void				parsing(t_print *t);
void				parsing_widht2(t_print *p);
void				parsing_precision2(t_print *p);
/*
**---------------------------------------------------------
*/
void				type_selection(t_print *p);
void				type_char(t_print *p);
/*
**---------------------------------------------------------
*/
void				type_point(t_print *p);
void				type_point2(t_print *p, char *dst, long long addr);
void				fill_point_null(t_print *p);
void				type_point_precision(t_print *p, long long addr);
void				type_point_fill(t_print *p, char *dst);
void				type_point_widht2(t_print *p);
/*
**---------------------------------------------------------
*/
void				type_str(t_print *p);
void				type_str_precision(t_print *p, char *s);
void				type_str_spe_fill(t_print *p, char *s, int len);
void				type_str_spe_fill2(t_print *p, char *s, int len);
/*
**---------------------------------------------------------
*/
void				type_u(t_print *p);
void				type_u_precision(t_print *p, char *s
		, unsigned long long nb);
unsigned long long	type_u_size(t_print *p, unsigned long long nb);
void				type_u_mod(t_print *p, unsigned long long nb);
void				type_u_spe_fill(t_print *p, char *s, unsigned long long nb);
/*
**---------------------------------------------------------
*/
void				type_hexa(t_print *p);
void				type_hexa_option(t_print *p, long long nb);
void				type_hexa_precision(t_print *p, char *s, long long nb);
long long			type_hexa_size(t_print *p, long long nb);
void				type_hexa_mod2(t_print *p, long long nb);
void				type_hexa_spe_fill(t_print *p, char *s, long long nb);
void				type_hexa_spe_fill2(t_print *p, char *s, long long nb);
/*
**----------------------------------------------------------
*/
void				type_hexa_cap(t_print *p);
void				type_hexa_cap_option(t_print *p, long long nb);
void				type_hexa_cap_precision(t_print *p, char *s, long long nb);
long long			type_hexa_cap_size(t_print*p, long long nb);
void				type_hexa_mod(t_print *p, long long nb);
void				type_hexa_basic_fill(t_print *p, char *s);
void				type_hexa_special_fill(t_print *p, char *s, long long nb);
void				type_hexa_cap_spefill2(t_print *p, char *s, long long nb);
/*
**------------------------------------------------------------
*/
void				type_octal(t_print *p);
void				type_octal_option(t_print *p);
void				type_octal_precision(t_print *p, char *s
		, unsigned long long addr);
unsigned long long	type_octal_size(t_print *p, unsigned long long addr);
void				type_octal_mod(t_print *p, unsigned long long addr);
void				typeospefill(t_print *p, char *s, unsigned long long addr);
void				free_type(char *tmp, char *s);
/*
**------------------------------------------------------------
*/
void				type_bin(t_print *p);
char				*type_bin_option(t_print *p, int nb, char *s);
void				type_bin_precision(t_print *p, char *s, int nb);
void				type_bin_mod(t_print *p, int nb);
void				type_bin_spe_fill(t_print *p, char *s, int nb);
/*
**------------------------------------------------------------
*/
void				type_int(t_print *p);
void				type_int_option(t_print *p, long long nb);
void				type_int_precision(t_print *p, char *s, long long nb);
long long			type_int_size(t_print *p, long long nb);
void				type_int_mod(t_print *p, long long nb);
void				type_int_mod2(t_print *p, long long nb);
void				type_int_spe_fill(t_print *p, char *s, long long nb);
char				*type_int_spe_fill2(t_print *p, char *s, long long nb);
void				type_int_spe_fill3(t_print *p, char *s, long long nb);
/*
**------------------------------------------------------------
*/
void				undefined_type(t_print *p);
/*
**------------------------------------------------------------
*/
int					ft_strchrf(char *s, int c, int i);
size_t				ft_strlen(const char *s);
char				*ft_unsigned_itoa(unsigned long long nbr);
char				*ft_itoa_base2(unsigned long long nb, char *base);
char				*ft_itoa(long long nbr);
int					ft_isdigit(int c);

/*
**-------------------------------------------------------------
*/
void				type_float(t_print *p);
char				*ft_itoa_float(double nb, t_print *p, int sign);
void				type_float_fill(t_print *p, char *s);
void				type_float_spe_fill(t_print *p, char *s);
void				type_float_option(t_print *p, int len, char *s, int sign);
void				type_float_precision(t_print *p, char *s, int len);
void				type_nan_widht(t_print *p, char *s);
void				type_inf_widht(t_print *p, char *s, int len);
int					get_float_sign(float nb, t_print *p, int i, int sign);
void				type_float_option2(t_print *p, int len, int sign);
float				type_float_size(t_print *p, double nb);
void				type_inf_widht2(t_print *p, char *s, int len);
void				type_nan(t_print *p, char *s);
void				type_inf(t_print *p, char *s, int sign, int len);
void				type_float2(t_print *p, double nb, int sign, char *s);

#endif
