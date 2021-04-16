/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 22:39:14 by devza             #+#    #+#             */
/*   Updated: 2021/04/16 16:08:47 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
        j = 0;
        while (pipe_cmds[j])
        {
            g_data.command = malloc(sizeof * g_data.command);
            g_data.command->block = i;
            g_data.command->pipe_pos = j;
            new_pipe = ft_check_redirections(pipe_cmds[j]);
            g_data.command->tokens = ft_split_pars(new_pipe, ' ');
            free(new_pipe);
            int k = 0;
            while (g_data.command->tokens[k])
            {
                char *tmp_free = g_data.command->tokens[k];
                g_data.command->tokens[k] = ft_strtrim(g_data.command->tokens[k], " ");
                free(tmp_free);
                k++;
            }
            g_data.command->n_tokens = k;
            if (g_data.cmds == NULL)
                g_data.cmds = ft_lstnew(g_data.command);
            else
                ft_lstadd_back(&g_data.cmds, ft_lstnew(g_data.command));
            j++;
        }
        ft_free_d_p(pipe_cmds);
        npipe = malloc(sizeof(int));
        *npipe = j - 1;
        if (g_data.n_pipe_cmd == NULL)
            g_data.n_pipe_cmd = ft_lstnew(npipe);
        else
            ft_lstadd_back(&g_data.n_pipe_cmd, ft_lstnew(npipe));
        i++;
    }
    ft_free_d_p(cmds);
}

int     ft_check_syntax(char *line)
{
    if (*line == '|' || *line == ';')
    {
        ft_printf("syn err\n");
        return 1;
    }
    return (0); 
}

int    ft_prompt(int argc, char **argv)
{
    if (argc >= 2)
        g_data.line = argv[2];
    else    
    {
        if (g_data.ret == 0)
        {
            ft_printf("\033[0;32m");
            ft_printf("minishell 👽 %d > ", g_data.ret);
            ft_printf("\033[0m");
        }
        else
        {
            ft_printf("\033[0;31m");
            ft_printf("minishell 👽 %d > ", g_data.ret);
            ft_printf("\033[0m");
        }
        get_next_line(1, &g_data.line);
    }
    if (!ft_check_syntax(g_data.line))
        ft_parse(g_data.line);
    if (argc < 2)
        free(g_data.line);
    return 1;
}

const char* __asan_default_options() { return "detect_leaks=0"; }

void sighandler(int dummy)
{
    if (g_data.n_fork == 0)
    {
        //ft_printf("%d\n", g_data.ret);
        ft_printf("\n");
        ft_printf("\033[0;32m");
        // if (g_data.ret == 130)
        //     g_data.ret = 130;
        // else
        //     g_data.ret = 1;
        ft_printf("minishell 👽 %d > ", g_data.ret = 1);
        ft_printf("\033[0m");
    }
    else
    {
        ft_printf("\n");
        g_data.ret = 130;
    }
}

int     main(int argc, char **argv, char **envp)
{
    
    t_list *newlist;
    t_list *pipe_list;
    t_command *command;
    int i;
    int j;
    ft_stock_envp(envp);
    g_data.ret = 0;
    int *tmp;
    g_data.count = 0;
    g_data.his_count = 0;
    //signal(SIGQUIT, intHandler);
    while (1)
    {
        signal(SIGINT, sighandler);
        ft_prompt(argc, argv);
        newlist = g_data.cmds;
        pipe_list = g_data.n_pipe_cmd;
        j = 0;
        while (pipe_list)
        {
            ft_stock_ret();
            g_data.num_pipes = *(int *)pipe_list->content;
            g_data.fdd = 0;
            g_data.n_fork = 0;
            g_data.fd[0] = 0;
            g_data.fd[1] = 1;
            //g_data.ret = 0;
            //ft_printf("n pipe %d\n", g_data.num_pipes);
            while(newlist && (((t_command *)newlist->content)->block == j))
            {
                command = (t_command *)newlist->content;
                //ft_printf("main : %p\n", command->tokens);
                ft_prepare_tokens(command);
                //ft_printf("**in :%d\n", command->input_file);
                //ft_printf("**out :%d\n", command->output_file);
                //ft_printf("n pipe %d\n", g_data.num_pipes);
                //ft_printf("%d : ****%s***\n", j, ((t_command *)newlist->content)->tokens[0]);
                // if (command->tokens[0] == NULL)
                // {
                //     newlist = newlist->next;
                //     continue;
                // }
                
                if (command->pipe_pos != g_data.num_pipes && g_data.num_pipes > 0)
                    pipe(g_data.fd);
                if (ft_check_builtin(command))
                {
                    //ft_printf("builtin\n");
                    ft_builtin(command);
                }
                else if (command->tokens[0] != NULL && command->tokens[0][0] != '\0')
                {
                    //ft_printf("bin\n");
                    ft_bin(command);
                }
                //waitpid(pid, NULL, 0);
                if (g_data.num_pipes > 0)
                {
                    close(g_data.fd[1]);
                    g_data.fdd = g_data.fd[0];
                    tmp = malloc(sizeof(int));
                    *tmp = g_data.fdd;
                    //ft_printf("%d\n", tmp);
                    ft_lstadd_back(&g_data.fd_close, ft_lstnew(tmp));
                    //close(g_data.fd[0]);
                }
                newlist = newlist->next;
            }
            ft_close_fd();
            //ft_printf("%d-", fdd);
            // while (g_data.fdd >= 3)
            // {
            //     //ft_printf("fdd : ");
            //     close(g_data.fdd);
            //     g_data.fdd--;
            // }                
            //ft_printf("%d", n_fork);
            //close(3);
            while (g_data.n_fork > 0)
            {
                //ft_printf("%d\n", g_data.ret);
                wait(&g_data.ret);
                g_data.ret /= 256;
                g_data.n_fork--;
                //close(g_data.fd[0]);
            }
            //ft_printf("%d\n", g_data.ret /= 256);
            // for(i = 0; i < num_pipes + 1; i++)
            // {
            //     wait(&g_data.ret);
            //     g_data.ret /= 256;
            // }
            pipe_list = pipe_list->next;
            j++;
        }
        if (argc >=2)
        {
            argc = 0;
            return g_data.ret;
        }
        ft_free_list();
    }
    return (0);
}