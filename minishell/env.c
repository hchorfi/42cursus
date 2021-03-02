/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 14:43:25 by hchorfi           #+#    #+#             */
/*   Updated: 2021/02/13 14:43:27 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_env()
{
    char *str_chr;
    int len;
    int chr_len;
    int i = 1;
    t_list *newlist;
    newlist = g_data.env_var;
    char *var;
    if (!g_command->tokens[1])
    {
        while(newlist)
        {   
			ft_putstr_fd(newlist->content, 1);
			write(1, "\n", 1);
            newlist = newlist->next;
        }
    }
    exit (0);
}

