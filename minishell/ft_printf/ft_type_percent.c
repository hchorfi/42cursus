/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_percent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 18:54:49 by hchorfi           #+#    #+#             */
/*   Updated: 2019/12/06 19:11:00 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void	ft_chk_special(t_flag *flags)
{
	if (flags->zswidth == '0')
	{
		if (flags->precision < 0)
			flags->zswidth = '0';
		if (g_tmp < 0)
			flags->zswidth = ' ';
	}
}

static	char	*ft_chk_width(t_flag *flags, int *slen, char *str)
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
		free(zspace);
		free(tmp);
		return (str);
	}
	return (str);
}

int				ft_type_percent(t_flag *flags)
{
	int		slen;
	char	*str;

	if (!(str = malloc(sizeof(char) * 2)))
		return (-1);
	str[0] = '%';
	str[1] = '\0';
	slen = 1;
	ft_chk_special(flags);
	str = ft_chk_width(flags, &slen, str);
	ft_putstr(str);
	slen = ft_strlen(str);
	free(str);
	return (slen);
}
