/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:35:17 by hchorfi           #+#    #+#             */
/*   Updated: 2021/04/13 13:43:50 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_strchr_set(char *str, char *set, char *token)
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
            {
                if (str[i] == '+' && token[i + 1] !='\0' && token[i + 1] == '=')
                {
                    j++;
                    continue;
                }
                else
                    return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

int     ft_valid_export_var(t_command *command, char *export_var, char *token, char *str)
{
    //ft_printf("%s : %s \n", export_var, token);
    // if (export_var[0] != '\'')
    //     export_var = remove_all_quotes(export_var);
    
    if(export_var[0] == '_' || (export_var[0] == '#' && command->n_tokens == 2))
        return (0);
    if (export_var[0] == '\0' || ft_isdigit(export_var[0]) || token[0] == '=' || (export_var[0] != '#' && ft_strchr_set(export_var, "$&|;-+=~!@^%{} []:?.#/,\'\\\"", token)))
    {
        ft_printf("minishell: %s: `", str);
        //ft_putstr_fd("minishell: export: `", 1);
        ft_putstr_fd(token, 1);
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

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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
    //char    *old_var;

    //ft_printf("%s : %s \n", export_var, token);

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
            //old_var = old_var;
            //ft_printf("%p\n", old_var);
        }
        else
        {
            old_var = newlist->content;
            //ft_printf("-%p\n", old_var);
        }
        //ft_printf("oldvar : %s - tokenvar : %s\n", old_var, export_var);
        if (!(ft_strcmp(old_var, export_var)))
        {
            //ft_printf("old : %s - export : %s\n", old_var, export_var);
            if(ft_strchr(newlist->content, '=') && !ft_strchr(token, '='))
            {
                if (ft_strchr(newlist->content, '='))
                {
                    //ft_printf("-free : %p\n", old_var);
                    free(old_var);
                }
                return (1);
            }
            //tmp_len = ft_strlen(tmp_str);
            if ((tmp_str = ft_strchr(token, '+')) != 0)
            {
                //ft_printf("--%s--", tmp_str + 2);
                if (ft_strchr(newlist->content, '='))
                {
                    //ft_printf("--free : %p\n", old_var);
                    free(old_var);
                }
                tmp_free = newlist->content;
                newlist->content = ft_strjoin(newlist->content, tmp_str + 2);
                free(tmp_free);
            }
            else
            {
                if (ft_strchr(newlist->content, '='))
                {
                    //ft_printf("---free : %p\n", old_var);
                    free(old_var);
                }
                tmp_free = newlist->content;
                newlist->content = ft_strdup(token);
                //ft_printf("----free : %p\n", tmp_free);
                free(tmp_free);
            }
            return (1);
        }
        else
        {
            if (ft_strchr(newlist->content, '='))
            {
                //ft_printf("-----free : %p\n", old_var);
                free(old_var);
            }
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
    //tmp = &g_data.env_var;
    //t_list *newlist = g_data.env_var;
    //ft_printf("i : %p - g_data : %p\n", *i, g_data.env_var);
    while (i)
    {
        //ft_printf("i : %s\n", (*i)->content);
        j = i->next;
        while (j)
        {
            i_data = ft_get_export_var(i->content);
            //ft_printf("i : %p - j : %p\n", i, j);
            //ft_printf("j : %s\n", j->content);
            j_data = ft_get_export_var(j->content);
            //ft_printf("-- i : %p > %s - j : %p > %s\n", i->content, i->content, j->content, j->content);
            if (strcmp(i_data, j_data) > 0)
            {
                 //ft_printf("swapped\n");
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
            // ft_printf("i : %s - j : %s\n", (*i)->content, j->content);
            j = j->next;
        }
        //ft_printf("--i : %p - g_data : %p\n", i, g_data.env_var);
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
            //ft_putstr_fd(newlist->content + len - chr_len + 1, 1);
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
            //ft_printf("-%p : %s-\n", command->tokens[i], command->tokens[i]);
            exp_var = ft_get_export_var(command->tokens[i]);
            if (exp_var[0] != '#' &&
                !(ft_valid_export_var(command, exp_var, command->tokens[i], "export")) &&
                !ft_exist_export_var(exp_var, command->tokens[i]))
            {
                //ft_printf("-%s-\n", command->tokens[i]);
                if ((tmp_str = ft_strchr(command->tokens[i], '+')) != 0)
                {
                    //printf("+");
                    ft_lstadd_back(&g_data.env_var, ft_lstnew(ft_strjoin(ft_substr(command->tokens[i], 0, ft_strlen(command->tokens[i]) - ft_strlen(tmp_str)), tmp_str + 1)));
                }
                else
                {   
                    //ft_printf("ok");
                    ft_lstadd_back(&g_data.env_var, ft_lstnew(ft_strdup(command->tokens[i])));
                }
            }
            if (ft_strchr(command->tokens[i], '='))
            {   
                //ft_printf("fr : % p\n");
                free(exp_var);
            }
            i++;
        }
    }
    return (0);
}
