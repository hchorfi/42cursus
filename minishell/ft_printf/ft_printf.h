/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 21:51:55 by hchorfi           #+#    #+#             */
/*   Updated: 2019/12/13 21:51:36 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <strings.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

typedef struct
{
	int		signe;
	int		width;
	int		precision;
	char	zswidth;
}			t_flag;

int			g_tmp;
int			ft_printf(const char *frmt, ...);
int			ft_type_d(va_list *args, t_flag *flags);
int			ft_type_c(va_list *args, t_flag *flags);
int			ft_type_percent(t_flag *flags);
int			ft_type_u(va_list *args, t_flag *flags);
int			ft_type_s(va_list *args, t_flag *flags);
int			ft_type_p(va_list *args, t_flag *flags);
int			ft_type_x(va_list *args, char *cfrmt, t_flag *flags);
int			ft_chk_cnv(va_list *args, char *cfrmt, t_flag *flags);
int			ft_isdigit(int c);
int			ft_strlen(const char *str);
char		*ft_itoa(int n);
char		ft_hexa_base(int n, char *cfrmt);
char		*ft_fill_width(int slen, t_flag *flags);
char		*ft_fill_zeros(int slen, t_flag *flags);
char		*ft_uitoa(unsigned int n);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_substr(const char *s, unsigned int start, size_t len);
void		ft_init_flags(t_flag *flags);
void		*ft_memset(void *b, int c, size_t len);
void		ft_putchar(char c);
void		ft_putstr(char *str);

#endif
