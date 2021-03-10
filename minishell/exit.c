/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:55:47 by hchorfi           #+#    #+#             */
/*   Updated: 2021/03/10 22:26:03 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_just_numbers(char *str)
{
	int		i;
	int		flag;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] != '\0')
	{
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r' || str[i] == '\f')
			i++;
		if(str[i] != '\0' && !ft_isdigit(str[i]))
			return (0);
		if (str[i] != '\0' && str[i + 1] == '\r')
			return (0);
		if (str[i] != '\0')
			i++;
	}
	return(1);
}

int		ft_exit()
{
	int		i;
	if(g_command->n_tokens > 1)
	{
		i = 1;
		while (i < g_command->n_tokens )
		{
			//ft_printf("--%s--\n",g_command->tokens[i]);
			if(!ft_just_numbers(g_command->tokens[i]))
			{
				ft_printf("minishell: exit: %s: numeric argument required\n", g_command->tokens[i]);
				return(g_data.ret = 255);
			}	
			i++;
		}
		if(g_command->n_tokens == 2)
			exit(atoi(g_command->tokens[1]));
		else
			ft_printf("minishell: exit: too many arguments\n");
		return(g_data.ret = 1);
	}
	else
		exit (0);
}
