/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:26:49 by hchorfi           #+#    #+#             */
/*   Updated: 2019/12/06 01:34:24 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	unsigned int	mlen;
	unsigned int	slen;
	char			*substr;

	i = 0;
	mlen = 0;
	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (start > slen)
		len = i;
	if (len > (slen - start))
		mlen = slen - start + 1;
	else
		mlen = len + 1;
	if (!(substr = malloc(mlen * sizeof(char))))
		return (NULL);
	while (s[start] != '\0' && i < len)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}
