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
        pipe_cmds = ft_split_pars(cmds[i], '|');
        //g_command->pipe_pos = 0;
        j = 0;
        while (pipe_cmds[j])
        {
            g_command = malloc(sizeof * g_command);
            g_command->block = i;
            g_command->pipe_pos = j;
            g_command->tokens = ft_split_pars(pipe_cmds[j], ' ');
            //printf("%s\n", g_command->tokens[0]);
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
    pid_t pid;
    int i;
    int j;
    int k;
    int num_pipes;
    int *pipefds;
    pipefds = NULL;
    int pipe_cmds;
    ft_stock_envp(envp);
    while (1)
    {
        ft_prompt();
        newlist = g_data.cmds;
        pipe_list = g_data.n_pipe_cmd;
        i = 0;
        j = 0;
        while (pipe_list)
        {
            num_pipes = *(int *)pipe_list->content;
            // if (num_pipes > 0)
            //     pipefds = (int *)malloc(sizeof (int) * (num_pipes * 2));
            // //printf("%d\n", num_pipes);
            // //printf("%d", pipefds[0]);
            // // while (pipefds[i])
            // // {
            // //     //close(pipefds[i]);
            // //     i++;
            // // }
            // //printf("%d", i);
            // //printf("command n %d\n", j);
            // k = 0;
            // while (k <= num_pipes - 1)
            // {
            //     pipe(pipefds + (k * 2));
            //     //ft_putnbr_fd(k, 1);
            //     k++;
            // }
            pipe_cmds = 0;
            int fd[2];
            int fdd = 0;
            while(newlist && (((t_command *)newlist->content)->block == j))
            {
                
                
                i = 0;
                pipe(fd);
                pid = fork();
                if (pid == 0)
                {
                    dup2(fdd, 0);
                    if (((t_command *)newlist->content)->pipe_pos != num_pipes && num_pipes > 0)
                        dup2(fd[1], 1);
                    close(fd[0]);
                    ft_exec(newlist->content);
                }
                else
                {
                    waitpid(pid, NULL, 0);
                    close(fd[1]);
                    fdd = fd[0];

                }
                // printf("tokens n : %d\n", ((t_command *)newlist->content)->pipe_pos);
                // printf("%d\n", num_pipes);
                // while (((t_command *)newlist->content)->tokens[i])
                // {
                //    printf("%s\n",((t_command *)newlist->content)->tokens[i]);
                //    i++;
                // }
                // printf("-----\n");


                //printf("pipe : %d\n", ((t_command *)newlist->content)->pipe_pos);
                

                newlist = newlist->next;
                pipe_cmds++;
                // // if ((pid = fork()) == 0)
                // //     ft_exec(newlist->content);
                // // else
                // //     wait(0);
                // pid = fork();
                // if (pid == 0)
                // {
                //     //printf("-----%d", ((t_command *)newlist->content)->pipe_pos);
                //     if (((t_command *)newlist->content)->pipe_pos != 0 && num_pipes > 0)
                //     {
                //         //ft_putstr_fd("----last---ok\n", 1);
                //         dup2(pipefds[(pipe_cmds - 1) * 2], 0);
                //         close(pipefds[(pipe_cmds - 1) * 2]);
                //         close(pipefds[(pipe_cmds - 1) ]);
                //         //ft_putnbr_fd(pipefds[(pipe_cmds - 1) * 2], 1);
                //     }
                //     if (((t_command *)newlist->content)->pipe_pos != num_pipes && num_pipes > 0)
                //     {
                //         //ft_putstr_fd("----first---ok\n", 1);
                //         close(pipefds[pipe_cmds * 2]);
                //         dup2(pipefds[(pipe_cmds * 2) + 1], 1);
                //         close(pipefds[(pipe_cmds * 2) + 1]);
                //         //close(pipefds[pipe_cmds * 2 + 1]);
                //         //ft_putnbr_fd(pipefds[pipe_cmds * 2 + 1], 1);
                //     }
                //     // k = num_pipes * 2;
                //     // while (k > 0)
                //     // {
                //     //     //ft_putnbr_fd(k, 1);
                //     //     close(pipefds[k - 2]);
                //     //     //close(pipefds[k - 1]);
                //     //     k = k - 2;
                //     // }
                    
                //     //ft_putnbr_fd(pipefds[0], 1);
                //     ft_exec(newlist->content);
                // }
                // else
                // {
                //     if (((t_command *)newlist->content)->pipe_pos != 0 && num_pipes > 0)
                //     {
                //         //ft_putstr_fd("----last---ok\n", 1);
                //         close(pipefds[(pipe_cmds - 1) * 2]);
                //         close(pipefds[((pipe_cmds - 1) * 2) + 1]);
                //         //ft_putnbr_fd(pipefds[(pipe_cmds - 1) * 2], 1);
                //     }
                //     if (((t_command *)newlist->content)->pipe_pos != num_pipes && num_pipes > 0)
                //     {
                //         //ft_putstr_fd("----first---ok\n", 1);
                //         //pipefds[pipe_cmds * 2];
                //         //pipefds[pipe_cmds * 2 + 1]
                //         //pipefds[(pipe_cmds - 1) * 2] = 
                //         //close(pipefds[pipe_cmds * 2 + 1]);
                //         //ft_putnbr_fd(pipefds[pipe_cmds * 2 + 1], 1);
                //     }
                //     // while (pipefds[i])
                //     // {
                //     //     close(pipefds[i]);
                //     //     i++;
                //     // }
                //     // k = num_pipes;
                //     k = num_pipes * 2;
                //     while (k > 0)
                //     {
                //         //ft_putnbr_fd(k, 1);
                //         //close(pipefds[k - 1]);
                //         k = k - 2;
                //     }
                //     waitpid(pid, NULL, 0);
                // }
                
            }
            // k = num_pipes;
            // while (k > 0)
            // {
            //     //ft_putnbr_fd(k, 1);
            //     close(pipefds[k]);
            //     close(pipefds[k - 1]);
            //     k--;
            // }
            //printf("number of pipes in command %d = %d\n", j, *(int *)pipe_list->content);
            //printf("*********\n");
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
