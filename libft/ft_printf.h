/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 02:09:51 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/25 20:57:13 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>

# define SPECIFIER "sSpbdDioOuUxXcC"
# define FLAG "1234567890#-+ .lhjz*"

enum { HASH, PLUS, MINUS, SPACE, ZERO, WIDTH, PREC, PREFIX };

typedef struct		s_str
{
	char			*str;
	size_t			len;
}					t_str;

typedef struct		s_data
{
	struct s_str	chunk;
	struct s_str	format;
	struct s_str	res;
	int				option[8];
}					t_data;

t_str				ft_chunkappend(t_str s1, t_str s2, char c);

t_str				ft_convert(t_data data, va_list ap, size_t size, int prec);
t_str				ft_apply(t_str res, int opt[8], char spec);
t_str				ft_applyint(t_str res, int opt[8], char spec);
size_t				ft_getsize(t_str chunk);
void				ft_parse_flag(t_data *data, va_list ap);
char				**ft_unicconv(char **str, int i, wchar_t c);
t_str				ft_loop(t_str fmt, va_list ap, int *error);

#endif
