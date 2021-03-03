/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:26:48 by hchorfi           #+#    #+#             */
/*   Updated: 2019/12/13 19:51:29 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	char	*ft_chk_width(t_flag *flags, int *slen, char *str)
{
	char	*zspace;

	zspace = NULL;
	if (flags->width - (*slen) > 0)
	{
		zspace = ft_fill_width(*slen, flags);
		if (flags->signe == 1)
			str = ft_strjoin(str, zspace);
		if (flags->signe == 0)
			str = ft_strjoin(zspace, str);
		free(zspace);
		return (str);
	}
	return (str);
}

static	char	*ft_chk_prec(t_flag *flags, int *slen, char *str)
{
	if (flags->precision >= 0 && *slen > flags->precision)
	{
		if (flags->precision == 0)
			str = ft_substr(str, 0, 0);
		else
			str = ft_substr(str, 0, flags->precision);
		*slen = ft_strlen(str);
		return (str);
	}
	return (str);
}

static	int		ft_chk_null(t_flag *flags)
{
	int		slen;
	char	*null;

	slen = 6;
	null = "(null)";
	if (flags->precision >= 0 && slen > flags->precision)
	{
		if (flags->precision == 0)
			null = ft_substr(null, 0, 0);
		else
			null = ft_substr(null, 0, flags->precision);
		slen = ft_strlen(null);
	}
	null = ft_chk_width(flags, &slen, null);
	ft_putstr(null);
	return (ft_strlen(null));
}

int				ft_type_s(va_list *args, t_flag *flags)
{
	int		slen;
	char	*str;

	str = va_arg(*args, char*);
	if (str == NULL)
		return (ft_chk_null(flags));
	slen = ft_strlen(str);
	str = ft_chk_prec(flags, &slen, str);
	str = ft_chk_width(flags, &slen, str);
	ft_putstr(str);
	slen = ft_strlen(str);
	return (slen);
}
