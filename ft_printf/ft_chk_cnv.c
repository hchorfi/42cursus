/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chk_cnv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 19:40:45 by hchorfi           #+#    #+#             */
/*   Updated: 2019/12/06 19:41:00 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_chk_cnv(va_list *args, char *cfrmt, t_flag *flags)
{
	if (*cfrmt == 'd' || *cfrmt == 'i')
		return (ft_type_d(args, flags));
	else if (*cfrmt == 'c')
		return (ft_type_c(args, flags));
	else if (*cfrmt == 'u')
		return (ft_type_u(args, flags));
	else if (*cfrmt == 's')
		return (ft_type_s(args, flags));
	else if (*cfrmt == 'x' || *cfrmt == 'X')
		return (ft_type_x(args, cfrmt, flags));
	else if (*cfrmt == '%')
		return (ft_type_percent(flags));
	else if (*cfrmt == 'p')
		return (ft_type_p(args, flags));
	return (0);
}
