/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 15:13:16 by hchorfi           #+#    #+#             */
/*   Updated: 2021/02/16 20:30:09 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_del_list(t_list **head, int position)
{
    t_list *curr;
    t_list *prev;
    
    curr = *head;
    prev = *head;
    if (*head == NULL)
        return (0);
    else if (position == 1)
    {
        *head = curr->next;
        free(curr);
        curr = NULL;
    }
    else
    {
        while (position != 1)
        {
            prev = curr;
            curr = curr->next;
            position--;
        }
        prev->next = curr->next;
        free(curr);
        curr = NULL; 
    }
    return (0);
}

int		ft_chr_var(char *unset_var)
{
	t_list  *newlist;
    char    *new_var;
    char    *old_var;
    char    *tmp_str;
    int     tmp_len;
    int     len;
    int     i;

    newlist = g_data.env_var;
    new_var = unset_var;
    i = 1;
    while (newlist)
    {
        if ((tmp_str = ft_strchr(newlist->content, '=')))
        {
            tmp_len = ft_strlen(tmp_str);
            len = ft_strlen(newlist->content);
            old_var = ft_substr(newlist->content, 0, len - tmp_len);
        }
        else
        {
            old_var = newlist->content;
            len = ft_strlen(old_var);
        }
        if (ft_strncmp(old_var, new_var, len) == 0)
        {   
            ft_del_list(&g_data.env_var,i);
            return 1;
        }
        newlist = newlist->next;
        i++;
    }
    return (0);
}

int		ft_valid_unset_var(char *unset_var)
{
	int		i;

	i = 0;
	if (unset_var[0] == '-')
    {
        ft_putstr_fd("we don't hundle option here ^_-\n", 1);
        return (0);
    }
	while (unset_var[i] != '\0')
    {
        if (!ft_isalnum(unset_var[i]) && unset_var[i] != '_')
        {
            ft_putstr_fd("bash: export: `", 1);
            ft_putstr_fd(unset_var, 1);
            ft_putstr_fd("': not a valid identifier\n", 1);
            return (0);
        }
		else
        	i++;
    }
	if (ft_isdigit(unset_var[0]))
	{
		ft_putstr_fd("bash: export: `", 1);
		ft_putstr_fd(unset_var, 1);
		ft_putstr_fd("': not a valid identifier\n", 1);
		return (0);
	}
	return (1);
}

int		ft_unset()
{
	t_list 	*printlist;
	t_list	*newlist;
	char    *new_var;
    char    *old_var;
    char    *tmp_str;
    int     tmp_len;
    int     len;
	int i = 0;

	// printlist = g_data.env_var;
	// newlist = g_data.env_var;
	// while (printlist)
	// {
	// 	printf("%d : %s\n", i, printlist->content);
	// 	printlist = printlist->next;
	// 	i++;
	// }

	i = 1;
	while (g_command.tokens[i])
	{
		if (ft_valid_unset_var(g_command.tokens[i]))
			ft_chr_var(g_command.tokens[i]);
		i++;
	}
	

	return (0);
}
