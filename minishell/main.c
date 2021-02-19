/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 22:39:14 by devza             #+#    #+#             */
/*   Updated: 2021/02/17 11:26:53 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_exec(void *cmd)
{   
    int pid;
    int status;

    g_command = (t_command *)cmd;
    if (!g_command->tokens[0])
        return (0);
    else if (!ft_memcmp(g_command->tokens[0], "export", 7))
        ft_export();
    else if(!ft_memcmp(g_command->tokens[0], "env", 4))
        ft_env();
    else if (!ft_memcmp(g_command->tokens[0], "unset", 6))
        ft_unset();
    else if (!ft_memcmp(g_command->tokens[0], "pwd", 4))
        ft_pwd();
    else if (!ft_memcmp(g_command->tokens[0], "cd", 3))
        ft_cd();
    else if (!ft_memcmp(g_command->tokens[0], "echo", 5))
        ft_echo();
    else
        ft_check_bin();
    return (0);
}

char    **ft_check_pipe(char *cmd)
{
    
    printf("%s\n", cmd);
    return NULL;
}

void    ft_parse(char *line)
{
    char **cmds = ft_split_pars(line, ';');
    char **pipe_cmds;
    g_data.cmds = NULL;
    g_data.n_pipe_cmd = NULL;
    int *npipe;
    int i = 0;
    int j;
    while (cmds[i])
    {
        g_command = malloc(sizeof * g_command);
        pipe_cmds = ft_split_pars(cmds[i], '|');
        j = 0;
        g_command->pipe_pos = 0;
        g_command->block = i + 1;
        while (pipe_cmds[j])
        {
            g_command->pipe_pos++;
            g_command->tokens = ft_split_pars(pipe_cmds[j], ' ');
            if (g_data.cmds == NULL)
                g_data.cmds = ft_lstnew(g_command);
            else
                ft_lstadd_back(&g_data.cmds, ft_lstnew(g_command));
            j++;
        }
        npipe = malloc(sizeof(int));
        *npipe = j - 1;
        if (g_data.n_pipe_cmd == NULL)
            g_data.n_pipe_cmd = ft_lstnew(npipe);
        else
            ft_lstadd_back(&g_data.n_pipe_cmd, ft_lstnew(npipe));
        i++;
    }
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
    t_list *newlist;
    t_list *pipe_list;

    ft_stock_envp(envp);
    while (1)
    {
        ft_prompt();
        newlist = g_data.cmds;
        pipe_list = g_data.n_pipe_cmd;
        int i = 0;
        int j = 1;
        while (pipe_list)
        {
            printf("command n %d\n", j);
            while(newlist && (((t_command *)newlist->content)->block == j))
            {
                //ft_exec(newlist->content);
                i = 0;
                while (((t_command *)g_data.cmds->content)->tokens[i])
                {
                    printf("%s\n",((t_command *)g_data.cmds->content)->tokens[i]);
                    i++;
                }
                newlist = newlist->next;
            }
            printf("number of pipes in command %d = %d\n", j, *(int *)pipe_list->content);
            pipe_list = pipe_list->next;
            j++;
        }
        
        // while(newlist)
        // {
            
        //     //ft_exec(newlist->content);
        //     newlist = newlist->next;
        //     i++;
        // }
    }
    
    /*
    ft_export("hamza=test");
    int i = 0;
    
    
    */
    return (0);
}
