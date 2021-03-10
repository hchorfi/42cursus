/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:55:47 by hchorfi           #+#    #+#             */
/*   Updated: 2021/03/10 18:55:55 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_exit()
{
	if(g_command->tokens[2])
	{
		ft_printf("minishell: exit: too many arguments\n");
		return(g_data.ret = 1);
	}
	if(g_command->tokens[1])
		exit(atoi(g_command->tokens[1]));
	else
		exit (0);
}
