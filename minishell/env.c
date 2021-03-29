/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 14:43:25 by hchorfi           #+#    #+#             */
/*   Updated: 2021/03/12 22:35:24 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_env(t_command *command)
{
    char *str_chr;
    int len;
    int chr_len;
    int i = 1;
    t_list *newlist;
    newlist = g_data.env_var;
    char *var;
    if (command->n_tokens == 1)
    {
        while(newlist)
        {   
            if(ft_strchr(newlist->content, '='))
            {
			    ft_putstr_fd(newlist->content, 1);
			    write(1, "\n", 1);
            }
            newlist = newlist->next;
        }
    }
    return (g_data.ret = 0);
}

