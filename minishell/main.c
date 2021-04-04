/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 22:39:14 by devza             #+#    #+#             */
/*   Updated: 2021/04/04 10:20:44 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_check_builtin(t_command *command)
{
    if (!command->tokens[0])
        return (0);
    else if (!ft_strncmp(command->tokens[0], "export", 7))
        return (1);
    else if(!ft_strncmp(command->tokens[0], "env", 4))
        return (1);
    else if (!ft_strncmp(command->tokens[0], "unset", 6))
        return (1);
    else if (!ft_strncmp(command->tokens[0], "pwd", 4))
        return (1);
    else if (!ft_strncmp(command->tokens[0], "cd", 3))
        return (1);
    else if (!ft_strncmp(command->tokens[0], "echo", 5))
        return (1);
    else if (!ft_strncmp(command->tokens[0], "exit", 5))
        return (1);
    else
        return 0;
}

// int     ft_exec(void *cmd)
// {
//     else if(!(ret = ft_check_bin()))
//     {
//         ft_printf("---%d\n", ret);
//         return (g_data.ret = 127);
//     }
//     //ft_printf("%d\n", ret);
//     else
//         return (g_data.ret = 0);
// }

int     ft_exec_builtin(t_command *command)
{
    if (!ft_strncmp(command->tokens[0], "export", 7))
        ft_export(command);
    else if(!ft_strncmp(command->tokens[0], "env", 4))
        ft_env(command);
    else if (!ft_strncmp(command->tokens[0], "unset", 6))
        return (ft_unset(command));
    else if (!ft_strncmp(command->tokens[0], "pwd", 4))
        ft_pwd();
    else if (!ft_strncmp(command->tokens[0], "cd", 3))
        ft_cd(command);
    else if (!ft_strncmp(command->tokens[0], "echo", 5))
        return (ft_echo(command));
    else if (!ft_strncmp(command->tokens[0], "exit", 5))
        ft_exit(command);
    return (0);
}

char    *ft_check_in(char *pipe_cmds)
{
    char *new_pipe;
    char **str;
    char *file;
    char *tmp_in;
    int in;
    int i = 0;
    char *tmp_free;
    char *tmp_free2;
    str = ft_split_pars(pipe_cmds, '<');
    new_pipe = ft_strdup("");
    int k = 0;

    while (str[i])
    {
        //ft_printf("-%s-\n", str[i]);
        if (i == 0 && *str[0] != '<')
        {
            //printf("--%d--%s--\n", i,str[i]);
            tmp_free = new_pipe;
            new_pipe = ft_strjoin(str[i], "");
            free(tmp_free);
            i++;
        }
        else
        {
            in = 0;
            if (i == 0 && *str[0] == '<')
               tmp_in = ft_strtrim(str[i] + 1, " ");
            else
                tmp_in = ft_strtrim(str[i], " ");
            int j = 0;
            //printf("--%d--%s--\n", i,tmp_in);
            if(tmp_in[j] == '\"' || tmp_in[j] == '\'')
            {
                int cot = j++;
                while (tmp_in[j] != tmp_in[cot] && tmp_in[j] != '\0')
                {
                    j++;
                }
            }
            else
            {
                while (tmp_in[j] != ' ' && tmp_in[j] != '\0')
                    j++;
            }
            file = ft_substr(tmp_in, 0, j);
            tmp_free2 = file;
            file = get_other_variables(file);
            free(tmp_free2);
            tmp_free2 = file;
            file = remove_all_quotes(file);
            //printf("in file : %s \n", file);
            if ((in = open(file, O_RDONLY)) == -1)
                ft_printf("minishell : %s No such file or directory\n", file);
            //ft_printf("*%d\n",in);
            if (g_data.command->input_file > 0)
                close(g_data.command->input_file);
            //ft_printf("in : %d\n", in);
            g_data.command->input_file = in;
            tmp_free = new_pipe;
            new_pipe = ft_strjoin(new_pipe, tmp_in + j);
            free(tmp_free);
            free(tmp_in);
            free(file);
            i++;
        }
    }
    //if (str[0])
    //ft_printf("***%d\n", g_data.command->input_file);
    ft_free_d_p(str);
    return (new_pipe);
}

char    *ft_check_redirections(char *pipe_cmds)
{
    char **str;
    //pipe_cmds = get_other_variables(pipe_cmds);
    str = ft_split_pars(pipe_cmds, '>');
    int i = 0;
    char *tmp_out;
    char *tmp_in;
    int out;
    char *file;
    char *new_pipe;
    char *tmp_free;
    char *tmp_free2;
    new_pipe = ft_strdup("");
    g_data.command->output_file = 1;

    while(str[i])
    {
        int priority = 0;
        //ft_printf("%s\n", str[i]);
        int append = 0;
        if (i == 0 && *str[0] != '>')
        {
            tmp_in = ft_check_in(str[i]);
            tmp_free = new_pipe;
            new_pipe = ft_strjoin(tmp_in,"");
            free(tmp_free);
            free(tmp_in);
            i++;
        }
        else
        {
            out = 1;
            if (i == 0 && *str[0] == '>')
                tmp_in = ft_check_in(str[i] + 1);
            else
                tmp_in = ft_check_in(str[i]);
            //ft_printf("-%s-\n", tmp_in);
            tmp_out = ft_strtrim(tmp_in, " ");
            //ft_printf("%p\n", tmp_out);
            free(tmp_in);
            int j = 0;
            //ft_printf("-%s\n", tmp_out);
            if (tmp_out[0] == '>')
            {
                tmp_out++;
                while (tmp_out[j] == ' ' && tmp_out[j] != '\0')
                    j++;
                append = 1;
            }
            //ft_printf("--%s\n", tmp_out + j);
            //if (tmp_out[j] != '\0')
            //tmp_out += j;
            //tmp_out + j;
            //ft_printf("-%s-\n", tmp_out);
            //ft_printf("-%c-\n", tmp_out[0]);
            //ft_printf("-%d-\n", j);
            if(/**tmp_out != '\0' && */(tmp_out[j] == '\"' || tmp_out[j] == '\''))
            {
                int cot = j++;
                while (tmp_out[j] != tmp_out[cot] && tmp_out[j] != '\0')
                {
                    j++;
                }
            }
            else
            {
                //ft_printf("ok\n");
                while (/**tmp_out != '\0' && */tmp_out[j] != ' ' && tmp_out[j] != '\0')
                    j++;
            }
            file = ft_substr(tmp_out, 0, j);
            //ft_printf("---%s\n", file);
            tmp_free2 = file;
            file = get_other_variables(file);
            free(tmp_free2);
            tmp_free2 = file;
            file = remove_all_quotes(file);
            free(tmp_free2);
            if (append == 0)
            {
                priority = 1;
                out = open(file, O_RDWR|O_CREAT|O_TRUNC, 0666);
                free(file);
            }
            else
            {
                struct stat path_stat;
                if (priority == 0 || stat(file, &path_stat))
                    out = open(file, O_RDWR|O_CREAT|O_APPEND, 0666);
                free(file);
            }
            if (g_data.command->output_file > 1)
                close(g_data.command->output_file);
            g_data.command->output_file = out;
            //ft_printf("tmp out + j : --%s--\n", tmp_out + j);
            //if (*tmp_out != '\0')
            //char *tmp_free = new_pipe;
            tmp_free = new_pipe;
            new_pipe = ft_strjoin(new_pipe, tmp_out + j);
            free(tmp_free);
            if (append == 1)
                free(tmp_out - 1);
            else 
                free(tmp_out);
            //free(tmp_free);
            i++;
        }
    }
    ft_free_d_p(str);
    //free(tmp_in);
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
        //command->pipe_pos = 0;
        j = 0;
        while (pipe_cmds[j])
        {
            g_data.command = malloc(sizeof * g_data.command);
            g_data.command->block = i;
            g_data.command->pipe_pos = j;
            new_pipe = ft_check_redirections(pipe_cmds[j]);
            //ft_printf("---%s--\n", new_pipe);
            //new_pipe = get_other_variables(new_pipe);
            g_data.command->tokens = ft_split_pars(new_pipe, ' ');
            free(new_pipe);
            int k = 0;
            while (g_data.command->tokens[k])
            {
                //command->tokens[k] = remove_all_quotes(command->tokens[k]);
                char *tmp_free = g_data.command->tokens[k];
                g_data.command->tokens[k] = ft_strtrim(g_data.command->tokens[k], " ");
                free(tmp_free);
                k++;
            }
            g_data.command->n_tokens = k;
            //ft_printf("in : %d - out : %d\n", command->input_file, command->output_file);
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

    //i = 0;
    // while (command->tokens[i])
    // {
    //     command->tokens[i] = ft_strtrim(command->tokens[i], " ");
    //     i++;
    // }
}

void    ft_stock_ret(void)
{
    char    *str;
    t_list  *env_list;
    int     exist;
    char    *tmp_free;

    exist = 0;
    env_list = g_data.env_var;
    str = ft_strjoin("?=", tmp_free = ft_itoa(g_data.ret));
    free(tmp_free);
    while (env_list)
    {
        if (*(char *)(env_list)->content == '?')
        {
            tmp_free = env_list->content;
            env_list->content = str;
            //free(tmp_free);
            exist = 1;
        }
        env_list = env_list->next;
    }
    if (!exist)
        ft_lstadd_back(&g_data.env_var, ft_lstnew(str));
}

int    ft_prompt(int argc, char **argv)
{
    char    *line;
    char    *tmp_line;
    int     len;
    int     line_len;
    int     ret;
    char     c;
    char    *str_char;
    char    *tmp_free;
    line = NULL;

    if (argc >= 2)
        line = argv[2];
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
        //ft_printf("%s\n",line);
        len = get_next_line(0, &line);
        line_len = ft_strlen(line);
        //ft_printf("len : %d, line_len : %d\n", len, line_len);
    }
    ft_parse(line);
    // if (!len && !line_len)
    // {
    //     ft_printf("\nexit\n");
    //     exit(0);
    // }
    if (argc < 2)
        free(line);
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

void    ft_prepare_tokens(t_command *command)
{
    //t_list  *cmds_list;
    char *tmp_free;
    int     k;
    k = 0;
    while (command->tokens[k])
    {
        //ft_printf("****%s***\n", ((t_command *)newlist->content)->tokens[k]);
        tmp_free = command->tokens[k];
        command->tokens[k] = get_other_variables(command->tokens[k]);
        free(tmp_free);
        //if (ft_strncmp(((t_command *)newlist->content)->tokens[0], "export", 7 ) && ft_strncmp(((t_command *)newlist->content)->tokens[0], "unset", 6 ))
        tmp_free = command->tokens[k];
        command->tokens[k] = remove_all_quotes(command->tokens[k]);
        free(tmp_free);
        //ft_printf("====%s====\n", ((t_command *)newlist->content)->tokens[k]);
        k++;
    }
}

void    ft_builtin(t_command *command)
{
    int     std_out;
    std_out = dup(1);
    int std_in = dup(0);
    if (command->input_file > 0)
    {
        dup2(command->input_file, 0);
        close(command->input_file);                            
    }
    else
        dup2(g_data.fdd, 0);
    if (command->pipe_pos != g_data.num_pipes && g_data.num_pipes > 0)
    {
        dup2(g_data.fd[1], 1);
    }
    if (command->output_file != 1)
    {
        dup2(command->output_file, 1);
        close(command->output_file);
    }
    ft_exec_builtin(command);
    //ft_printf("%d", g_data.ret);
    dup2(std_out, 1);
    dup2(std_in, 0);
    close(std_out);
    close(std_in);
}


void    ft_bin(t_command *command)
{
    g_data.n_fork++;
    if (!fork())
    {
        //ft_printf("fork\n");
        int std_out = dup(1);
        int std_in = dup(0);
        //ft_printf("--in :%d\n", command->input_file);
        //ft_printf("--out :%d\n", command->output_file);
        //ft_printf("fdd : %d\n", g_data.fdd);
        if (command->input_file > 0 && command->input_file < 1024)
        {
            //ft_printf("in :%d\n", command->input_file);
            dup2(command->input_file, 0);
            close(command->input_file);                            
        }
        else
        {   
            dup2(g_data.fdd, 0);
            //close(g_data.fdd);
        }
        if (g_data.num_pipes > 0)
        {
            if (command->pipe_pos != g_data.num_pipes)
                dup2(g_data.fd[1], 1);
            close(g_data.fd[0]);
            close(g_data.fd[1]);
        }
        if (command->output_file > 1 && command->output_file < 1024)
        {
            //ft_printf("out :%d\n", command->output_file);
            dup2(command->output_file, 1);
            close(command->output_file);
        }
        //ft_printf("fd[0] : %d - fd[1] : %d\n", g_data.fd[0], g_data.fd[1]);
        ft_exec_bin(command);
        dup2(std_out, 1);
        dup2(std_in, 0);
        close(std_out);
        close(std_in);
        ft_printf("minishell: %s: command not found\n", command->tokens[0]);
        exit(g_data.ret = 127);
    }
}

void    ft_close_fd()
{
    t_list  *tmp_list;

    while (g_data.fd_close)
    {
        tmp_list = g_data.fd_close;
       //ft_printf("close : %d\n", *(int *)(g_data.fd_close)->content);
        //if (*(int *)(g_data.fd_close)->content > 2)
            close(*(int *)(g_data.fd_close)->content);
        free(g_data.fd_close->content);
        g_data.fd_close = g_data.fd_close->next;
        free(tmp_list);
    }
}

void    ft_free_list()
{
    t_list  *tmp_list;

    //if (!i)
    //{
    while (g_data.cmds)
    {
        tmp_list = g_data.cmds;
        ft_free_d_p(((t_command *)g_data.cmds->content)->tokens);
        if (((t_command *)g_data.cmds->content)->input_file > 0)
            close(((t_command *)g_data.cmds->content)->input_file);
        if (((t_command *)g_data.cmds->content)->output_file > 1)
            close(((t_command *)g_data.cmds->content)->output_file);
        free(g_data.cmds->content);
        g_data.cmds = g_data.cmds->next;
        free(tmp_list);
    }
    while (g_data.n_pipe_cmd)
    {
        tmp_list = g_data.n_pipe_cmd;
        free(g_data.n_pipe_cmd->content);
        g_data.n_pipe_cmd = g_data.n_pipe_cmd->next;
        free(tmp_list);
    }
    //}
    // else
    // {
    //     while (g_data.env_var)
    //     {
    //         tmp_list = g_data.env_var;
    //         free(g_data.env_var->content);
    //         g_data.env_var = g_data.env_var->next;
    //         free(tmp_list);
    //     }
    // }
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
                ft_prepare_tokens(command);
                //ft_printf("**in :%d\n", command->input_file);
                //ft_printf("**out :%d\n", command->output_file);
                //ft_printf("n pipe %d\n", g_data.num_pipes);
                //ft_printf("%d : ****%s***\n", j, ((t_command *)newlist->content)->tokens[0]);
                if (command->tokens[0] == NULL)
                {
                    newlist = newlist->next;
                    continue;
                }
                if (command->pipe_pos != g_data.num_pipes && g_data.num_pipes > 0)
                    pipe(g_data.fd);
                if (ft_check_builtin(command))
                {
                    //ft_printf("builtin\n");
                    ft_builtin(command);
                }
                else
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
    //ft_free_list(1);
    return (0);
}