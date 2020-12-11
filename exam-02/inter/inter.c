/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 10:20:30 by hchorfi           #+#    #+#             */
/*   Updated: 2020/03/06 14:13:06 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int check(char *s, char c, int i)
{
	int j = 0;
	while (j < i)
	{
		if (s[j] == c)
			return 1;
		j++;
	}
	return 0;
}

int main(int argc, char **argv)
{
	int i = 0;
	int j = 0;

	if (argc == 3)
	{
		while (argv[2][j])
			j++;
		while (argv[1][i])
		{
			if (!(check(argv[1], argv[1][i], i)) && check(argv[2], argv[1][i],j))
				write(1,&argv[1][i],1);
			i++;
		}
		write(1,"\n",1);
	}
}
