/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:54:06 by hchorfi           #+#    #+#             */
/*   Updated: 2019/12/06 19:01:35 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*ft_hexalong(unsigned long long n)
{
	unsigned long long	x;
	unsigned long long	nb;
	char				*xtr;
	char				*cfrmt;

	x = 1;
	nb = n;
	while (nb / 16)
	{
		nb = nb / 16;
		x++;
	}
	if (!(xtr = malloc((x + 1) * sizeof(char))))
		return (NULL);
	xtr[x] = '\0';
	if ((cfrmt = ft_strdup("x")) == NULL)
		return (NULL);
	while (n / 16)
	{
		xtr[--x] = ft_hexa_base((n % 16), cfrmt);
		n = n / 16;
	}
	xtr[--x] = ft_hexa_base((n % 16), cfrmt);
	free(cfrmt);
	return (xtr);
}

static	void	ft_chk_special(t_flag *flags, int *slen, char **str, int var)
{
	if (flags->zswidth == '0' && flags->precision >= 0)
		flags->zswidth = ' ';
	if (flags->precision == 0 && var == 0)
	{
		*str = ft_substr(*str, 0, 2);
		*slen = ft_strlen(*str);
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

static	char	*ft_chk_width(t_flag *flags, int *slen, char *str)
{
	char	*zspace;
	char	*tmp;

	zspace = NULL;
	tmp = str;
	if ((flags->width - (*slen)) > 0)
	{
		zspace = ft_fill_width(*slen, flags);
		if (flags->signe == 1)
			str = ft_strjoin(str, zspace);
		if (flags->signe == 0)
			str = ft_strjoin(zspace, str);
		free(zspace);
		free(tmp);
		return (str);
	}
	return (str);
}

int				ft_type_p(va_list *args, t_flag *flags)
{
	unsigned long long	var;
	int					slen;
	char				*str;
	char				*tmp;

	var = va_arg(*args, unsigned long long);
	if ((str = ft_hexalong(var)) == NULL)
		return (-1);
	tmp = str;
	str = ft_strjoin("0x", str);
	slen = ft_strlen(str);
	ft_chk_special(flags, &slen, &str, var);
	str = ft_chk_precision(flags, &slen, str);
	str = ft_chk_width(flags, &slen, str);
	ft_putstr(str);
	slen = ft_strlen(str);
	free(str);
	free(tmp);
	return (slen);
}
