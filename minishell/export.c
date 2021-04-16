/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:35:17 by hchorfi           #+#    #+#             */
/*   Updated: 2021/04/16 12:12:18 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_valid_export_var(t_command *command, char *export_var, char *token, char *str)
{
    if(export_var[0] == '_' || (export_var[0] == '#' && command->n_tokens == 2))
        return (0);
    if (export_var[0] == '\0' || ft_isdigit(export_var[0]) || token[0] == '=' || (export_var[0] != '#' && ft_strchr_set(export_var, "$&|;-+=~!@^%{} []:?.#/,\'\\\"", token)))
    {
        ft_printf("minishell: %s: `", str);
        ft_putstr_fd(token, 1);
        ft_putstr_fd("': not a valid identifier\n", 1);
        return (g_data.ret = 1);
    }
    return (0);
}

int     ft_exist_export_var(char *export_var, char *token)
{
    t_list  *newlist;
    char    *old_var;
    char    *tmp_str;
    int     tmp_len;
    int     len;
    char    *tmp_free;
    int     ex_join;
    
    newlist = g_data.env_var;
    if (ft_strchr(token, '+'))
    {               
        tmp_len = ft_strlen(export_var);
        export_var = ft_substr(export_var, 0, tmp_len - 1);
    }
    while (newlist)
    {
        ex_join = 0;
        if ((tmp_str = ft_strchr(newlist->content, '=')))
        {
            tmp_len = ft_strlen(tmp_str);
            len = ft_strlen(newlist->content);
            old_var = ft_substr(newlist->content, 0, len - tmp_len);
        }
        else
            old_var = newlist->content;
        if (!(ft_strcmp(old_var, export_var)))
        {
            if(ft_strchr(newlist->content, '=') && !ft_strchr(token, '='))
            {
                if (ft_strchr(newlist->content, '='))
                    free(old_var);
                return (1);
            }
            if ((tmp_str = ft_strchr(token, '+')) != 0)
            {
                if (ft_strchr(newlist->content, '='))
                    free(old_var);
                tmp_free = newlist->content;
                newlist->content = ft_strjoin(newlist->content, tmp_str + 2);
                free(tmp_free);
            }
            else
            {
                if (ft_strchr(newlist->content, '='))
                    free(old_var);
                tmp_free = newlist->content;
                newlist->content = ft_strdup(token);
                free(tmp_free);
            }
            return (1);
        }
        else
        {
            if (ft_strchr(newlist->content, '='))
                free(old_var);
        }
        newlist = newlist->next;
    }
    return (0);
}

void    ft_print_export2(char *str)
{
    int     i;

    i = 0;
    while(str[i] != '\0')
    {
        if (str[i] == '\\' || str[i] == '$')
            write(1, "\\", 1);
        write(1, &str[i], 1);
        i++;
    }
}

void    ft_sort_export()
{
    t_list *i;
    t_list *j;
    char   *i_data;
    char   *j_data;
    char   *tmp_data;

    i = g_data.env_var;
    while (i)
    {
        j = i->next;
        while (j)
        {
            i_data = ft_get_export_var(i->content);
            j_data = ft_get_export_var(j->content);
            if (strcmp(i_data, j_data) > 0)
            {
                 char *tmp_freei = i->content;
                 char *tmp_freej = j->content;
                 tmp_data = i->content;
                 i->content = j->content;
                 j->content = tmp_data;
                if (ft_strchr(tmp_freei , '='))
                    free(i_data);
                if (ft_strchr(tmp_freej , '='))
                    free(j_data);
            }
            else
            {
                if (ft_strchr(i->content , '='))
                    free(i_data);
                if (ft_strchr(j->content , '='))
                    free(j_data);
            }
            j = j->next;
        }
        i = i->next;
    }
}

void    ft_print_export()
{
    char    *str_chr;
    int     len;
    int     chr_len;
    t_list  *newlist;
    char    *var;


    ft_sort_export();
    newlist = g_data.env_var;
    while(newlist)
    {   
        char *tmp_str = newlist->content;
        if ((tmp_str[0] == '_' && tmp_str[1] == '=') || tmp_str[0] == '?')
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
            ft_print_export2(newlist->content + len - chr_len + 1);
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

int     ft_export(t_command *command)
{
    int     i;
    int     j;
    char    *exp_var;
    char    *tmp_str;
    
    i = 1;
    g_data.ret = 0;
    if (command->n_tokens == 1 || (command->n_tokens = 2 && command->tokens[1][0] == '#'))
        ft_print_export();
    else
    {
        while (command->tokens[i])
        {
            ft_printf("%s\n", command->tokens[i]);
            exp_var = ft_get_export_var(command->tokens[i]);
            if (exp_var[0] != '#' &&
                !(ft_valid_export_var(command, exp_var, command->tokens[i], "export")) &&
                !ft_exist_export_var(exp_var, command->tokens[i]))
            {
                if ((tmp_str = ft_strchr(command->tokens[i], '+')) != 0)
                    ft_lstadd_back(&g_data.env_var, ft_lstnew(ft_strjoin(ft_substr(command->tokens[i], 0, ft_strlen(command->tokens[i]) - ft_strlen(tmp_str)), tmp_str + 1)));
                else
                    ft_lstadd_back(&g_data.env_var, ft_lstnew(ft_strdup(command->tokens[i])));
            }
            if (ft_strchr(command->tokens[i], '='))
                free(exp_var);
            i++;
        }
    }
    return (0);
}
