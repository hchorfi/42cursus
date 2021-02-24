/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 21:06:02 by hchorfi           #+#    #+#             */
/*   Updated: 2019/12/06 19:53:57 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void	ft_chk_special(t_flag *flags, char **str, int *slen, int var)
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

static	char	*ft_precision(t_flag *flags, char *str, int *slen, int var)
{
	char	*zspace;

	zspace = NULL;
	if (flags->precision >= 0 && flags->precision - (*slen) >= 0)
	{
		if (var < 0)
			(*slen)--;
		zspace = ft_fill_zeros(*slen, flags);
		str = ft_strjoin(zspace, str);
		if (var < 0)
		{
			str[0] = '-';
			str[flags->precision - (*slen)] = '0';
		}
		*slen = ft_strlen(str);
		free(zspace);
		zspace = NULL;
		return (str);
	}
	return (str);
}

static	char	*ft_width(t_flag *flags, char *str, int *slen, int var)
{
	char	*zspace;
	char	*tmp;

	zspace = NULL;
	tmp = str;
	if (flags->width - (*slen) > 0)
	{
		zspace = ft_fill_width(*slen, flags);
		if (flags->signe == 1)
			str = ft_strjoin(str, zspace);
		if (flags->signe == 0)
			str = ft_strjoin(zspace, str);
		if (var < 0 && flags->zswidth == '0')
		{
			str[0] = '-';
			str[flags->width - (*slen)] = '0';
		}
		free(zspace);
		free(tmp);
		zspace = NULL;
		return (str);
	}
	return (str);
}

int				ft_type_d(va_list *args, t_flag *flags)
{
	int		var;
	int		slen;
	char	*str;

	var = va_arg(*args, int);
	str = ft_itoa(var);
	slen = ft_strlen(str);
	ft_chk_special(flags, &str, &slen, var);
	str = ft_precision(flags, str, &slen, var);
	str = ft_width(flags, str, &slen, var);
	ft_putstr(str);
	slen = ft_strlen(str);
	free(str);
	return (slen);
}
