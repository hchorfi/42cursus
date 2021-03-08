/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 22:39:14 by devza             #+#    #+#             */
/*   Updated: 2021/03/07 12:46:09 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_check_builtin(void *cmd)
{
    g_command = (t_command *)cmd;
    if (!g_command->tokens[0])
        return (0);
    else if (!ft_strncmp(g_command->tokens[0], "export", 7))
        return (1);
    else if(!ft_strncmp(g_command->tokens[0], "env", 4))
        return (1);
    else if (!ft_strncmp(g_command->tokens[0], "unset", 6))
        return (1);
    else if (!ft_strncmp(g_command->tokens[0], "pwd", 4))
        return (1);
    else if (!ft_strncmp(g_command->tokens[0], "cd", 3))
        return (1);
    else if (!ft_strncmp(g_command->tokens[0], "echo", 5))
        return (1);
    else
        return 0;
}

// int     ft_exec(void *cmd)
// {
   
//     else if(!(ret = ft_check_bin()))
//     {
//             ft_printf("---%d\n", ret);
//         return (g_data.ret = 127);
//     }
//     //ft_printf("%d\n", ret);
//     else
//         return (g_data.ret = 0);
// }
int     ft_exec_builtin(void *cmd)
{
    g_command = (t_command *)cmd;

    if (!ft_strncmp(g_command->tokens[0], "export", 7))
        ft_export();
    else if(!ft_strncmp(g_command->tokens[0], "env", 4))
        ft_env();
    else if (!ft_strncmp(g_command->tokens[0], "unset", 6))
        ft_unset();
    else if (!ft_strncmp(g_command->tokens[0], "pwd", 4))
        ft_pwd();
    else if (!ft_strncmp(g_command->tokens[0], "cd", 3))
        ft_cd();
    else if (!ft_strncmp(g_command->tokens[0], "echo", 5))
        ft_echo();
    return (0);
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
    new_pipe = ft_strdup("");
    
    while (str[i])
    {
        
        if (i == 0 && *str[0] != '<')
        {
            //printf("--%d--%s--\n", i,str[i]);
            new_pipe = ft_strjoin(str[i], "");
            i++;
        }
        else
        {
            if (i == 0 && *str[0] == '<')
                str[0]++;
            tmp_in = ft_strtrim(str[i], " ");
            int j = 0;
            //printf("--%d--%s--\n", i,tmp_in);
            while (tmp_in[j] != ' ' && tmp_in[j] != '\0')
                j++;
            file = ft_substr(tmp_in, 0, j);
            //printf("in file : %s \n", file);
            if ((in = open(file, O_RDONLY)) == -1)
                ft_printf("minishell : %s No such file or directory\n", file);
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
    new_pipe = ft_strdup("");
    while(str[i])
    {
        if (i == 0 && *str[0] != '>')
        {
            tmp_in = ft_check_in(str[i]);
            new_pipe = ft_strjoin(tmp_in,"");
            i++;
        }
        else
        {
            if (i == 0 && *str[0] == '>')
                str[0]++;
            //ft_printf("---%s\n", str[0]);
            tmp_in = ft_check_in(str[i]);
            
            tmp_out = ft_strtrim(tmp_in, " ");
            int j = 0;
            //ft_printf("---%s\n", tmp_out);
            while (tmp_out[j] != ' ' && tmp_out[j] != '\0')
                j++;
            file = ft_substr(tmp_out, 0, j);
            out = open(file, O_RDWR|O_CREAT, 0666);
            //ft_printf("tmp out + j : --%s--\n", tmp_out + j);
            new_pipe = ft_strjoin(new_pipe, tmp_out + j);
            i++;
        }
    }
    g_command->output_file = out;
    //ft_printf("---%s--\n", new_pipe);
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
            //ft_printf("---%s--\n", new_pipe);
            g_command->tokens = ft_split_pars(new_pipe, ' ');
            // int k = 0;
            // while (g_command->tokens[k])
            // {
            //     ft_printf("--%s\n", g_command->tokens);
            //     k++;
            // }
            //ft_printf("in : %d - out : %d\n", g_command->input_file, g_command->output_file);
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

int    ft_prompt(char **argv)
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
    int std_out;
    out = 1;
    in = 0;
    g_data.ret = 0;
    ft_stock_envp(envp);
    while (1)
    {
        ft_prompt(argv);
        newlist = g_data.cmds;
        pipe_list = g_data.n_pipe_cmd;
        j = 0;
        while (pipe_list)
        {
            num_pipes = *(int *)pipe_list->content;
            fdd = 0;
            while(newlist && (((t_command *)newlist->content)->block == j))
            {
                //ft_printf("****%s***\n", ((t_command *)newlist->content)->tokens[0]);
                if (((t_command *)newlist->content)->tokens[0] == NULL)
                    break;
                i = 0;
                if (((t_command *)newlist->content)->pipe_pos != num_pipes && num_pipes > 0)
                    pipe(fd);
                if (ft_check_builtin(newlist->content))
                {
                    //ft_printf("builtin\n");
                    std_out = dup(1);
                    //int std_in = dup(0);
                    if (((t_command *)newlist->content)->input_file > 0)
                    {
                        dup2(((t_command *)newlist->content)->input_file, 0);
                        close(((t_command *)newlist->content)->input_file);                            
                    }
                    else
                        dup2(fdd, 0);
                    if (((t_command *)newlist->content)->pipe_pos != num_pipes && num_pipes > 0)
                    {
                        dup2(fd[1], 1);
                    }
                    if (((t_command *)newlist->content)->output_file != 1)
                    {
                        dup2(((t_command *)newlist->content)->output_file, 1);
                        close(((t_command *)newlist->content)->output_file);
                    }
                    ft_exec_builtin(newlist->content);
                    dup2(std_out, 1);
                    //dup2(std_in, 0);
                    close(std_out);
                    //close(std_in);
                }
                else
                {
                    //ft_printf("bin\n");
                    pid = fork();
                    if (pid == 0)
                    {
                        std_out = dup(1);
                        int std_in = dup(0);
                        if (((t_command *)newlist->content)->input_file > 0)
                        {
                            dup2(((t_command *)newlist->content)->input_file, 0);
                            close(((t_command *)newlist->content)->input_file);                            
                        }
                        else
                            dup2(fdd, 0);
                        if (((t_command *)newlist->content)->pipe_pos != num_pipes && num_pipes > 0)
                        {
                            dup2(fd[1], 1);
                        }
                        close(fd[0]);
                        if (((t_command *)newlist->content)->output_file != 1)
                        {
                            dup2(((t_command *)newlist->content)->output_file, 1);
                            close(((t_command *)newlist->content)->output_file);
                        }
                        ft_exec_bin(newlist->content);
                    }
                }
                //waitpid(pid, NULL, 0);
                if (num_pipes > 0)
                {
                    close(fd[1]);
                    fdd = fd[0];
                }
                newlist = newlist->next;
            }
            //ft_printf("%d-", fdd);
            while (fdd >= 3)
            {
                close(fdd);
                fdd--;
            }
            for(i = 0; i < num_pipes + 1; i++)
                wait(NULL);
            pipe_list = pipe_list->next;
            j++;
        }
    }
    return (0);
}