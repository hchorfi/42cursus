/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_zeros.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:37:33 by hchorfi           #+#    #+#             */
/*   Updated: 2019/12/02 15:46:25 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_fill_zeros(int slen, t_flag *flags)
{
	char	*zspace;

	if (!(zspace = malloc((flags->precision - slen + 1) * sizeof(char))))
		return (NULL);
	ft_memset(zspace, '0', (flags->precision - slen));
	zspace[flags->precision - slen] = '\0';
	return (zspace);
}
