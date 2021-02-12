/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 22:39:14 by devza             #+#    #+#             */
/*   Updated: 2021/02/11 19:08:54 by hchorfi          ###   ########.fr       */
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
            ft_putstr_fd("': not a valid identifier1\n", 1);
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
        ft_putstr_fd("': not a valid identifier2\n", 1);
        return (0);
    }
    return (1);
}

int     ft_exist_export_var(char *export_var)
{
    t_list  *newlist;
    int     tmp_var_len;
    int     tmp_chr_len;
    char    *new_var;
    char    *old_var;

    newlist = g_data.env_var;
    tmp_var_len = ft_strlen(export_var);
    tmp_chr_len = ft_strlen(ft_strchr(export_var, '='));
    new_var = ft_substr(export_var, 0, tmp_var_len - tmp_chr_len + 1);  
    while (newlist)
    {
        tmp_var_len = ft_strlen(newlist->content);
        tmp_chr_len = ft_strlen(ft_strchr(newlist->content, '='));
        old_var = ft_substr(newlist->content, 0, tmp_var_len - tmp_chr_len + 1);
        tmp_var_len = ft_strlen(old_var);
        if (!ft_memcmp(new_var, old_var, tmp_var_len));
        {
            free(new_var);
            free(old_var);
            return (1);
        }
        newlist = newlist->next;
    }
    free(new_var);
    free(old_var);
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
            if (ft_valid_export_var(g_command.tokens[i]))
            {
                if (ft_exist_export_var(g_command.tokens[i]))
                    printf("exist");
                else
                    ft_lstadd_back(&g_data.env_var, ft_lstnew(g_command.tokens[i]));
            }
            i++;
        }
    }
    return (1);
}

int     ft_exec()
{   
    int pid;
    int status;
    
    if (!ft_memcmp(g_command.tokens[0], "export", 7))
    {
        ft_export();
    }
    pid = fork();
    if (pid == 0)
        execve(ft_strjoin("/bin/", g_command.tokens[0]), g_command.tokens, NULL);
    else
        wait(&status);
    return (1);
}

void    ft_parse(char *line)
{
    int i=0;
    g_command.tokens = ft_split(line, ' ');
}

int    ft_prompt()
{
    char    *line;

    ft_putstr_fd("\033[0;32m", 1);
    ft_putstr_fd("minishell 👽 > ", 1);
    ft_putstr_fd("\033[0m", 1);
	get_next_line(0, &line);
    ft_parse(line);
    return 1;
}

void    ft_stock_envp(char **envp)
{
    int     i;
    
    i = 0;
    g_data.env_var = NULL;
    while (envp[i])
    {
        if (g_data.env_var == NULL)
            g_data.env_var = ft_lstnew(envp[i]);
        else
            ft_lstadd_back(&g_data.env_var, ft_lstnew(envp[i]));
        i++;
    }
    // g_data.env_var->next = NULL;
}

int     main(int argc, char **argv, char **envp)
{
    
    ft_stock_envp(envp);
    while (1)
    {
        ft_prompt();
        ft_exec();
    }
    
    /*
    ft_export("hamza=test");
    int i = 0;
    
    
    */
    return (0);
}
