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

int     ft_exec()
{   
    int pid;
    int status;
    
    if (!ft_memcmp(g_command.tokens[0], "export", 7))
        ft_export();
    else if(!ft_memcmp(g_command.tokens[0], "env", 4))
        ft_env();
    else if (!ft_memcmp(g_command.tokens[0], "unset", 6))
        ft_unset();
    else
    {
        pid = fork();
        if (pid == 0)
            execve(ft_strjoin("/bin/", g_command.tokens[0]), g_command.tokens, NULL);
        else
            wait(&status);
    }
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
