/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:35:17 by hchorfi           #+#    #+#             */
/*   Updated: 2021/02/12 16:35:18 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_valid_export_var(char *export_var)
{
    int i;

    i = 0;
    if (export_var[i] == '-')
    {
        ft_putstr_fd("we don't hundle option here ^_-\n", 1);
        return (0);
    }
    while (export_var[i] != '=' && export_var[i] != '\0')
    {
        if (ft_memchr(export_var, '-', i + 1))
        {
            ft_putstr_fd("bash: export: `", 1);
            ft_putstr_fd(export_var, 1);
            ft_putstr_fd("': not a valid identifier\n", 1);
            return (0);
        }
        i++;
    }
    if(export_var[0] == '_')
        return (1);
    if (ft_isdigit(export_var[0]))
    {
        ft_putstr_fd("bash: export: `", 1);
        ft_putstr_fd(export_var, 1);
        ft_putstr_fd("': not a valid identifier\n", 1);
        return (0);
    }
    return (1);
}

int     ft_exist_export_var(char *export_var)
{
    t_list  *newlist;
    char    *new_var;
    char    *old_var;
    char    *tmp_str;
    int     tmp_len;
    int     len;

    newlist = g_data.env_var;
    if ((tmp_str = ft_strchr(export_var, '=')))
    {
        tmp_len = ft_strlen(tmp_str);
        len = ft_strlen(export_var);
        new_var = ft_substr(export_var, 0, len - tmp_len);
    }
    else
        new_var = export_var;
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
        if (!(ft_memcmp(old_var, new_var, len)))
        {
            newlist->content = ft_strdup(export_var);
            return 1;
        }
        newlist = newlist->next;
    }
    return (0);
}

int     ft_export()
{
    char *str_chr;
    int len;
    int chr_len;
    int i = 1;
    t_list *newlist;
    newlist = g_data.env_var;
    char *var;
    if (!g_command.tokens[1])
    {
        while(newlist)
        {   
            char *tmp_str = newlist->content;
            if (tmp_str[0] == '_' && tmp_str[1] == '=')
            {
                newlist = newlist->next;
                continue;
            }
            ft_putstr_fd("declare -x ", 1);
            if ((str_chr = ft_strchr(newlist->content, '=')))
            {
                len = ft_strlen(newlist->content);
                chr_len = ft_strlen(str_chr);
                var = ft_substr(newlist->content, 0, len - chr_len + 1);
                ft_putstr_fd(var, 1);
                write(1, "\"", 1);
                ft_putstr_fd(newlist->content + len - chr_len + 1, 1);
                write(1, "\"", 1);
                write(1, "\n", 1);
                free(var);
            }
            else
            {
                ft_putstr_fd(newlist->content, 1);
                write(1, "\n", 1);
            }
            newlist = newlist->next;
            //i++;
        }
    }
    else
    {
        while (g_command.tokens[i])
        {
            if (ft_valid_export_var(g_command.tokens[i]) && !ft_exist_export_var(g_command.tokens[i]))
                ft_lstadd_back(&g_data.env_var, ft_lstnew(g_command.tokens[i]));
            i++;
        }
    }
    return (1);
}
