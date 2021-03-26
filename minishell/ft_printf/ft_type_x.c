/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:02:01 by hchorfi           #+#    #+#             */
/*   Updated: 2019/12/11 02:32:44 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			ft_hexa_base(int n, char *cfrmt)
{
	if (n == 10)
		return ((*cfrmt == 'x') ? 'a' : 'A');
	else if (n == 11)
		return ((*cfrmt == 'x') ? 'b' : 'B');
	else if (n == 12)
		return ((*cfrmt == 'x') ? 'c' : 'C');
	else if (n == 13)
		return ((*cfrmt == 'x') ? 'd' : 'D');
	else if (n == 14)
		return ((*cfrmt == 'x') ? 'e' : 'E');
	else if (n == 15)
		return ((*cfrmt == 'x') ? 'f' : 'F');
	else
		return (*ft_itoa(n));
}

char			*ft_hexa(unsigned int n, char *cfrmt)
{
	unsigned	int	x;
	unsigned	int	nb;
	char			*xtr;

	x = 1;
	nb = n;
	while (nb / 16)
	{
		nb = nb / 16;
		x++;
	}
	xtr = malloc((x + 1) * sizeof(char));
	xtr[x] = '\0';
	while (n / 16)
	{
		xtr[--x] = ft_hexa_base((n % 16), cfrmt);
		n = n / 16;
	}
	xtr[--x] = ft_hexa_base((n % 16), cfrmt);
	return (xtr);
}

static	void	ft_chk_special(t_flag *flags, int *slen, char **str, int var)
{
	if (flags->precision < 0 && g_tmp < 0)
		flags->zswidth = ' ';
	if (flags->zswidth == '0' && flags->precision >= 0)
		flags->zswidth = ' ';
	if (flags->precision == 0 && var == 0)
	{
		if (flags->width > 0)
			*str[0] = ' ';
		else
			*str[0] = '\0';
		*slen = 1;
	}
}

static	char	*ft_chk_precision(t_flag *flags, int *slen, char *str)
{
	char	*zspace;

	zspace = NULL;
	if (flags->precision >= 0 && flags->precision - (*slen) > 0)
	{
		zspace = ft_fill_zeros(*slen, flags);
		str = ft_strjoin(zspace, str);
		*slen = ft_strlen(str);
		free(zspace);
		zspace = NULL;
		return (str);
	}
	return (str);
}

int				ft_type_x(va_list *args, char *cfrmt, t_flag *flags)
{
	unsigned int	var;
	int				slen;
	char			*str;
	char			*zspace;

	zspace = NULL;
	var = va_arg(*args, unsigned int);
	str = ft_hexa(var, cfrmt);
	slen = ft_strlen(str);
	ft_chk_special(flags, &slen, &str, var);
	str = ft_chk_precision(flags, &slen, str);
	if (flags->width - slen > 0)
	{
		zspace = ft_fill_width(slen, flags);
		if (flags->signe == 1)
			str = ft_strjoin(str, zspace);
		if (flags->signe == 0)
			str = ft_strjoin(zspace, str);
		free(zspace);
	}
	ft_putstr(str);
	slen = ft_strlen(str);
	free(str);
	return (slen);
}
