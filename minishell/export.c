/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:35:17 by hchorfi           #+#    #+#             */
/*   Updated: 2021/03/12 22:48:24 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_strchr_set(char *str, char *set)
{
    int     i;
    int     j;

    i = 0;
    while (str[i] != '\0')
    {
        j = 0;
        while (set[j] != '\0')
        {
            if (str[i] == set[j])
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

int     ft_valid_export_var(char *export_var, char *token, char *str)
{
    //ft_printf("%s : %s \n", export_var, token);
    if (export_var[0] != '\'')
        export_var = remove_all_quotes(export_var);
    if(export_var[0] == '_' || (export_var[0] == '#' && g_command->n_tokens == 2))
        return (0);
    if (ft_isdigit(export_var[0]) || token[0] == '=' || (export_var[0] != '#' && ft_strchr_set(export_var, "$&|;-+=~!@^%{} []:?.#/,\'\\\"")))
    {
        ft_printf("minishell: %s: `", str);
        //ft_putstr_fd("minishell: export: `", 1);
        ft_putstr_fd(remove_all_quotes(token), 1);
        ft_putstr_fd("': not a valid identifier\n", 1);
        return (g_data.ret = 1);
    }
    // if (ft_isdigit(export_var[0]) || export_var[0] == '=' ||
    //     export_var[0] == 0 || export_var[0] == '\'' || export_var[0] == '-')
    // {
    //     ft_putstr_fd("minishell: export: `", 1);
    //     ft_putstr_fd(remove_all_quotes(export_var), 1);
    //     ft_putstr_fd("': not a valid identifier\n", 1);
    //     return (g_data.ret = 1);
    // }
    return (0);
}

int     ft_exist_export_var(char *export_var, char *token)
{
    t_list  *newlist;
    char    *old_var;
    char    *tmp_str;
    int     tmp_len;
    int     len;

    newlist = g_data.env_var;
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
        if (!(ft_strncmp(old_var, export_var, len)))
        {
            if(!strchr(newlist->content, '='))
                newlist->content = ft_strdup(token);
            return 1;
        }
        newlist = newlist->next;
    }
    return (0);
}

void    ft_print_export()
{
    char    *str_chr;
    int     len;
    int     chr_len;
    t_list  *newlist;
    char    *var;

    newlist = g_data.env_var;
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
    }
}

char    *ft_get_export_var(char *exp_token)
{
    char    *exp_var;
    char    *tmp_str;
    int     tmp_len;
    int     len;

    if ((tmp_str = ft_strchr(exp_token, '=')))
    {
        tmp_len = ft_strlen(tmp_str);
        len = ft_strlen(exp_token);
        exp_var = ft_substr(exp_token, 0, len - tmp_len);
    }
    else
        exp_var = exp_token;
    return(exp_var);
}

int     ft_export()
{
    int     i;
    int     j;
    char    *exp_var;
    
    i = 1;
    if (g_command->n_tokens == 1 || (g_command->n_tokens = 2 && g_command->tokens[1][0] == '#'))
        ft_print_export();
    else
    {
        while (g_command->tokens[i])
        {
            //ft_printf("%s\n", g_command->tokens[i]);
            exp_var = ft_get_export_var(g_command->tokens[i]);
            if (exp_var[0] != '#' &&
                !(ft_valid_export_var(exp_var, g_command->tokens[i], "export")) &&
                !ft_exist_export_var(exp_var, g_command->tokens[i]))
                {
                    ft_lstadd_back(&g_data.env_var, ft_lstnew(remove_all_quotes(g_command->tokens[i])));
                }
            i++;
        }
    }
    return (g_data.ret);
}
