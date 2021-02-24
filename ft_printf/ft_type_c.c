/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 20:58:32 by hchorfi           #+#    #+#             */
/*   Updated: 2019/12/08 22:00:08 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void	ft_print_r(t_flag *flags, int var, int *slen)
{
	ft_putchar(var);
	while ((flags->width + 1) > ++(*slen))
		ft_putchar(' ');
}

static	void	ft_print_l(t_flag *flags, int var, int *slen)
{
	while ((flags->width + 1) > ++(*slen))
		ft_putchar(' ');
	ft_putchar(var);
}

int				ft_type_c(va_list *args, t_flag *flags)
{
	int	slen;
	int	var;

	var = va_arg(*args, int);
	slen = 1;
	if (flags->width - 1 > 0)
	{
		if (flags->signe == 1)
			ft_print_r(flags, var, &slen);
		if (flags->signe == 0)
			ft_print_l(flags, var, &slen);
	}
	else
		ft_putchar(var);
	return ((flags->width - 1 > 0) ? (slen - 1) : slen);
}
