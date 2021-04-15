#include "minishell.h"

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
        if (i == 0 && *str[0] != '<')
        {
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
            if ((in = open(file, O_RDONLY)) == -1)
                ft_printf("minishell : %s No such file or directory\n", file);
            if (g_data.command->input_file > 0)
                close(g_data.command->input_file);
            g_data.command->input_file = in;
            tmp_free = new_pipe;
            new_pipe = ft_strjoin(new_pipe, tmp_in + j);
            free(tmp_free);
            free(tmp_in);
            free(file);
            i++;
        }
    }
    ft_free_d_p(str);
    return (new_pipe);
}

char    *ft_check_redirections(char *pipe_cmds)
{
    char **str;
    if (*pipe_cmds == '>')
        str = ft_split_pars(pipe_cmds, '>');
    else
        str = csplit(pipe_cmds, '>');
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
            tmp_out = ft_strtrim(tmp_in, " ");
            free(tmp_in);
            int j = 0;
            if (tmp_out[0] == '>')
            {
                tmp_out++;
                while (tmp_out[j] == ' ' && tmp_out[j] != '\0')
                    j++;
                append = 1;
            }
            if((tmp_out[j] == '\"' || tmp_out[j] == '\''))
            {
                int cot = j++;
                while (tmp_out[j] != tmp_out[cot] && tmp_out[j] != '\0')
                {
                    j++;
                }
            }
            else
            {
                while (tmp_out[j] != ' ' && tmp_out[j] != '\0')
                    j++;
            }
            file = ft_substr(tmp_out, 0, j);
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
            tmp_free = new_pipe;
            new_pipe = ft_strjoin(new_pipe, tmp_out + j);
            free(tmp_free);
            if (append == 1)
                free(tmp_out - 1);
            else 
                free(tmp_out);
            i++;
        }
    }
    ft_free_d_p(str);
    return (new_pipe);
}