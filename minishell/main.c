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

char    *ft_check_redirections(char *pipe_cmds, t_command **g_command)
{
    char **str;
    str = ft_split_pars(pipe_cmds, '>');
    int i = 0;
    char *tmp;
    char *out_file;
    while(str[i])
    {
        i++;
        tmp = ft_strtrim(str[i], " ");
        int j = 0;
        while (str[i][j] != ' ')
            j++;
        
        ft_putstr_fd(str[i], 1);
        ft_putstr_fd("\n", 1);
        i++;
    }
    
    return (pipe_cmds);
}

void    ft_parse(char *line)
{
    char **cmds = ft_split_pars(line, ';');
    char **pipe_cmds;
    char *new_pipe;
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
            new_pipe = ft_check_redirections(pipe_cmds[j], &g_command);
            ft_putstr_fd(new_pipe, 1);
            ft_putstr_fd("\n", 1);
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
    int num_pipes;
    int fd[2];
    int fdd;
    int in;
    int out;
    out = 1;
    in = 0;
    ft_stock_envp(envp);
    while (1)
    {
        ft_prompt();
        // newlist = g_data.cmds;
        // pipe_list = g_data.n_pipe_cmd;
        // j = 0;
        // while (pipe_list)
        // {
        //     num_pipes = *(int *)pipe_list->content;
        //     fdd = 0;
        //     while(newlist && (((t_command *)newlist->content)->block == j))
        //     {
        //         i = 0;
        //         while (((t_command *)newlist->content)->tokens[i])
        //         {
        //             if (*((t_command *)newlist->content)->tokens[i] == '>')
        //             {
        //                 ((t_command *)newlist->content)->tokens[i] = NULL;
        //                 i++;
        //                 if(((t_command *)newlist->content)->tokens[i])
        //                 {
        //                     out = open(((t_command *)newlist->content)->tokens[i], O_RDWR|O_CREAT, 0666);
        //                     ((t_command *)newlist->content)->tokens[i] = NULL;
        //                     i++;
        //                 }
        //             }
        //             else
        //                 i++;
        //         }
        //         pipe(fd);
        //         pid = fork();
        //         if (pid == 0)
        //         {
        //             dup2(fdd, 0);
        //             if (((t_command *)newlist->content)->pipe_pos != num_pipes && num_pipes > 0)
        //                 dup2(fd[1], 1);
        //             close(fd[0]);
        //             if (out > 1)
        //             {
        //                 dup2(out, 1);
        //                 close(out);
        //             }
        //             ft_exec(newlist->content);
        //         }
        //         else
        //         {
        //             waitpid(pid, NULL, 0);
        //             close(fd[1]);
        //             fdd = fd[0];
        //             if (out > 1)
        //                 close(out);
        //         }
        //         newlist = newlist->next;
        //     }
        //     pipe_list = pipe_list->next;
        //     j++;
        //}

    }
    return (0);
}