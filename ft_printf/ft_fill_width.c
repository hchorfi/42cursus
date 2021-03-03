/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_width.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:17:08 by hchorfi           #+#    #+#             */
/*   Updated: 2019/12/04 18:25:10 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_fill_width(int slen, t_flag *flags)
{
	char	*zspace;

	if (!(zspace = malloc((flags->width - slen + 1) * sizeof(char))))
		return (NULL);
	ft_memset(zspace, flags->zswidth, (flags->width - slen));
	zspace[flags->width - slen] = '\0';
	return (zspace);
}
