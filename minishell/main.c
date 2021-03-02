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

char    *ft_check_in(char *pipe_cmds)
{
    char *new_pipe;
    char **str;
    char *file;
    char *tmp_in;
    int in = 0;
    int i = 0;

    str = ft_split_pars(pipe_cmds, '<');
    
    
    while (str[i])
    {
        
        if (i == 0)
        {
            //printf("--%d--%s--\n", i,str[i]);
            new_pipe = ft_strjoin(str[i], "");
            i++;
        }
        else
        {
            tmp_in = ft_strtrim(str[i], " ");
            int j = 0;
            //printf("--%d--%s--\n", i,tmp_in);
            while (tmp_in[j] != ' ' && tmp_in[j] != '\0')
                j++;
            file = ft_substr(tmp_in, 0, j);
            //printf("in file : %s \n", file);
            in = open(file, O_RDONLY);
            new_pipe = ft_strjoin(new_pipe, tmp_in + j);
            i++;
        }
    }
    g_command->input_file = in;
    return (new_pipe);
}

char    *ft_check_redirections(char *pipe_cmds)
{
    char **str;
    str = ft_split_pars(pipe_cmds, '>');
    int i = 0;
    char *tmp_out;
    char *tmp_in;
    int out = 1;
    char *file;
    char *new_pipe;
    while(str[i])
    {
        if (i == 0)
        {
            tmp_in = ft_check_in(str[i]);
            new_pipe = ft_strjoin(tmp_in,"");
            i++;
        }
        else
        {
            tmp_in = ft_check_in(str[i]);
            tmp_out = ft_strtrim(tmp_in, " ");
            int j = 0;
            while (tmp_out[j] != ' ' && tmp_out[j] != '\0')
                j++;
            file = ft_substr(tmp_out, 0, j);
            out = open(file, O_RDWR|O_CREAT, 0666);
            new_pipe = ft_strjoin(new_pipe, tmp_out + j);
            i++;
        }
    }
    g_command->output_file = out;
    return (new_pipe);
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
            new_pipe = ft_check_redirections(pipe_cmds[j]);
            //printf("%s\n", new_pipe);
            g_command->tokens = ft_split_pars(new_pipe, ' ');
            //printf("%s\n", g_command->tokens[0]);
            // int k = 0;
            // while (g_command->tokens[k])
            // {
            //     g_command->tokens[k] = ft_strtrim(g_command->tokens[k], " ");
            //     k++;
            // }
            // ft_putnbr_fd(g_command->input_file, 1);
            // ft_putnbr_fd(g_command->output_file, 1);
            // ft_putstr_fd("\n", 1);
            //printf("in : %d - out : %d", g_command->input_file, g_command->output_file);
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

int     ft_builtin(void *cmd)
{
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
        return 0;
    return 1;
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
    g_data.ret = 0;
    ft_stock_envp(envp);
    while (1)
    {
        ft_prompt();
        newlist = g_data.cmds;
        pipe_list = g_data.n_pipe_cmd;
        j = 0;
        while (pipe_list)
        {
            num_pipes = *(int *)pipe_list->content;
            fdd = 0;
            while(newlist && (((t_command *)newlist->content)->block == j))
            {
                //ft_builtin(newlist->content);
                i = 0;
                pipe(fd);
                pid = fork();
                if (pid == 0)
                {
                    if (((t_command *)newlist->content)->input_file != 0)
                        dup2(((t_command *)newlist->content)->input_file, 0);
                    else
                        dup2(fdd, 0);
                    if (((t_command *)newlist->content)->pipe_pos != num_pipes && num_pipes > 0)
                    {
                        dup2(fd[1], 1);
                    }
                    close(fd[0]);
                    if (((t_command *)newlist->content)->output_file != 1)
                            dup2(((t_command *)newlist->content)->output_file, 1);
                    ft_exec(newlist->content);
                }
                waitpid(pid, NULL, 0);
                close(fd[1]);
                fdd = fd[0];
                newlist = newlist->next;
            }
            while (fdd >= 3)
            {
                close(fdd);
                fdd--;
            }
            pipe_list = pipe_list->next;
            j++;
        }
    }
    return (0);
}