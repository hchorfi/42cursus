/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:57:44 by hchorfi           #+#    #+#             */
/*   Updated: 2019/12/15 20:47:36 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_nn(unsigned int n, int i)
{
	if (n <= 9)
		i++;
	if (n >= 10)
	{
		i++;
		while (n >= 10)
		{
			i++;
			n = n / 10;
		}
	}
	return (i);
}

char			*ft_uitoa(unsigned int n)
{
	char			*itoa;
	int				i;
	int				len;

	i = 0;
	len = ft_nn(n, i);
	if (!(itoa = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	itoa[len--] = '\0';
	while (len >= i)
	{
		itoa[len--] = (n % 10) + 48;
		n = n / 10;
	}
	return (itoa);
}

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

static	char	*ft_chk_precision(t_flag *flags, int *slen, char *str)
{
	char *zspace;

	zspace = NULL;
	if (flags->precision >= 0 && flags->precision - (*slen) > 0)
	{
		zspace = ft_fill_zeros((*slen), flags);
		str = ft_strjoin(zspace, str);
		*slen = ft_strlen(str);
		free(zspace);
		zspace = NULL;
		return (str);
	}
	return (str);
}

int				ft_type_u(va_list *args, t_flag *flags)
{
	unsigned	int	var;
	int				slen;
	char			*str;
	char			*zspace;

	zspace = NULL;
	var = va_arg(*args, unsigned int);
	str = ft_uitoa(var);
	slen = ft_strlen(str);
	ft_chk_special(flags, &str, &slen, var);
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
