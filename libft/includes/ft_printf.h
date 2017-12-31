/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 14:08:19 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/07 15:53:05 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <wchar.h>
# include "libft.h"
# include "ft_printf_list.h"

t_ftplst	*ft_get_flag(const char *format);
size_t		ft_printf_skip_nullchar(char *str, int nbnullchar);
void		ft_printf_search_prec(t_ftplst *list, va_list *ap);
void		ft_printf_search_field(t_ftplst *list, va_list *ap);
void		ft_printf_clear_flag(t_ftplst *list, va_list *ap);
void		ft_printf_switch(t_ftplst *list, va_list *ap);
void		ft_printf_load_struct(t_ftplst *list, va_list *ap);
void		ft_printf_tolst(t_ftplst *list, va_list *ap);
char		*ft_conv_c(t_ftplst *list, va_list *ap);
char		*ft_conv_di(t_ftplst *list, va_list *ap);
char		*ft_conv_o(t_ftplst *list, va_list *ap);
char		*ft_conv_b(t_ftplst *list, va_list *ap);
char		*ft_conv_u(t_ftplst *list, va_list *ap);
char		*ft_conv_xp_xup(t_ftplst *list, va_list *ap);
char		*ft_conv_lc_cup(t_ftplst *list, va_list *ap);
char		*ft_conv_ls_sup(t_ftplst *list, va_list *ap);
char		*ft_conv_s(t_ftplst *list, va_list *ap);
char		*ft_conv_percent(t_ftplst *list);
char		*ft_conv_p(t_ftplst *list, va_list *ap);
char		*ft_conv_not_valid(t_ftplst *list);
void		ft_printf_field(t_ftplst *list, char c);
void		ft_printf_field_di(t_ftplst *list, char c);
void		ft_printf_prec(t_ftplst *list);
void		ft_printf_prec_s(t_ftplst *list);
char		*ft_printf_lenmod_i(char *flag, va_list *ap, int i);
char		*ft_printf_lenmod_ui(char *flag, va_list *ap, int i, int base);
char		*ft_printf_attribute_space(char *res);
void		ft_printf_attribute_sharp(t_ftplst *list, char c);
char		ft_printf_attribute_zero(t_ftplst *list);
char		ft_printf_attribute_zero_char(t_ftplst *list);
char		ft_printf_attribute_zero_num(t_ftplst *list);
void		ft_printf_attribute_sign(t_ftplst *list);
void		ft_printf_attribute_sign_di(t_ftplst *list);
int			ft_isattribute(char c);
int			ft_islenmod(char c);
int			ft_printf_search_conv(t_ftplst *list);
int			ft_printf_get_field(char *flag);
int			ft_printf_get_prec(char *flag);
int			ft_printf_get_zero(char *flag);
int			ft_printf_get_minus(char *flag);
int			ft_printf(const char *format, ...);

#endif
