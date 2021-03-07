/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 11:48:51 by hchorfi           #+#    #+#             */
/*   Updated: 2021/03/05 12:27:21 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void	ft_wdth(va_list *args, char **frmt, int *skiped, t_flag *flags)
{
	int	nwidth;

	nwidth = 0;
	while (ft_isdigit(*(*frmt)))
	{
		nwidth = (nwidth * 10) + *(*frmt) - '0';
		(*frmt)++;
		(*skiped)++;
	}
	if (*(*frmt) == '*')
	{
		nwidth = va_arg(*args, int);
		(*frmt)++;
		(*skiped)++;
		if (nwidth < 0 && flags->signe == 0)
			flags->signe = 1;
	}
	g_tmp = nwidth;
	flags->width = nwidth > 0 ? nwidth : -nwidth;
}

static	void	ft_prec(va_list *args, char **frmt, int *skiped, t_flag *flags)
{
	int	nwidth;

	if (*(*frmt) == '.')
	{
		nwidth = 0;
		(*frmt)++;
		(*skiped)++;
		while (ft_isdigit(*(*frmt)))
		{
			nwidth = (nwidth * 10) + *(*frmt) - '0';
			(*frmt)++;
			(*skiped)++;
		}
		if (*(*frmt) == '*')
		{
			nwidth = va_arg(*args, int);
			(*frmt)++;
			(*skiped)++;
		}
		flags->precision = nwidth;
	}
}

int				ft_chk_flags(char *frmt, t_flag *flags, va_list *args)
{
	int skiped;

	skiped = 0;
	while (*frmt == '-')
	{
		flags->signe = 1;
		frmt++;
		skiped++;
	}
	if (*frmt == '0')
		flags->zswidth = '0';
	ft_wdth(args, &frmt, &skiped, flags);
	ft_prec(args, &frmt, &skiped, flags);
	return (skiped);
}

static	void	ft_ptchr(char *frmt, int *printed)
{
	ft_putchar(*frmt);
	(*printed)++;
}

int				ft_printf(const char *frmt, ...)
{
	int		printed;
	int		tmp;
	t_flag	flags;
	va_list args;

	va_start(args, frmt);
	printed = 0;
	while (*frmt)
	{
		ft_init_flags(&flags);
		if (*frmt == '%')
		{
			frmt++;
			frmt += ft_chk_flags((char *)frmt, &flags, &args);
			if ((tmp = ft_chk_cnv(&args, (char *)frmt, &flags)) == -1)
				return (-1);
			printed += tmp;
		}
		else
			ft_ptchr((char *)frmt, &printed);
		frmt++;
	}
	va_end(args);
	return (printed);
}
