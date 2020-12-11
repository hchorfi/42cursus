/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 17:47:05 by hchorfi           #+#    #+#             */
/*   Updated: 2020/03/06 14:31:15 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
int already(char *s, char c, int len)
{
	int i = 0;
	while (i < len)
	{	
		if (s[i] == c)
		{	
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int i = 0;

	if (argc == 3)
	{
		while(argv[1][i])
		{
			if (!(already(argv[1], argv[1][i], i)))
			{
				write(1, &argv[1][i], 1);
			}
			i++;
		}
		int len = i;
		i = 0;
		while(argv[2][i])
		{
			if (!(already(argv[1], argv[2][i], len)) && !(already(argv[2], argv[2][i], i)))
			{
				write(1, &argv[2][i], 1);
			}
			i++;
		}
	}
	write(1, "\n", 1);
}
