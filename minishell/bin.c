/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:05:25 by hchorfi           #+#    #+#             */
/*   Updated: 2021/04/18 14:20:52 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_path()
{
	char	*path;
	char	*tmp;
	int		len;
	t_list	*newlist;

	newlist = g_data.env_var;
	path = NULL;
	while (newlist)
	{
		tmp = ft_substr(newlist->content, 0, 5);
		if (!ft_strncmp(tmp, "PATH=", 6))
		{
			path = ft_strchr(newlist->content, '=');
			free (tmp);
			return (path + 1);
		}
		else
			newlist = newlist->next;
		free (tmp);
	}
	return (path);
}

int		ft_exec_bin(t_command *command)
{
	int		pid;
	int		status;
	char	**bins;
	char	*path;
	char	*file;
	int		i;
	struct stat path_stat;
	char	**envp;
	//command = (t_command *)cmd;
	if(!stat(command->tokens[0], &path_stat))
	{
		//ft_printf("%s : exist\n", command->tokens[0]);
		if(!ft_strncmp(command->tokens[0], "..", 3))
		{
			ft_printf("minishell: %s: command not found\n", command->tokens[0]);
			exit(127);		
		}
		if(!ft_strncmp(command->tokens[0], ".", 2))
		{
			ft_putstr_fd("bash: .: filename argument required\n.: usage: . filename [arguments]\n", 1);
			exit(2);	
		}
		if (path_stat.st_mode & S_IFDIR)
		{
			if (command->tokens[0][0] != '.' && command->tokens[0][0] != '/' && command->tokens[0][ft_strlen(command->tokens[0]) - 1] != '/')
			{
				ft_printf("minishell: %s: command not found\n", command->tokens[0]);
        		exit(g_data.ret = 127);
			}
			else
			{
				ft_printf("minishell: %s: is a directory\n", command->tokens[0]);
				exit(126);
			}
		}
		//printf("%o\n", path_stat.st_mode);
		//ft_printf("%d\n", S_IRWXU);
		if(path_stat.st_mode == S_IRWXU  || path_stat.st_mode == S_IRWXO || path_stat.st_mode == S_IRWXG || ((path_stat.st_mode & S_IXUSR) && (path_stat.st_mode & S_IRUSR)))
		{
			//printf("OK");
			//if(!fork())
			//{
				envp = ft_get_envp();
				execve(command->tokens[0], command->tokens, envp);
			//}
			
            //wait(&g_data.ret);
			//ft_free_d_p(envp);
			exit (0);
			
		}
		else
		{
			//printf("OK2");
			//ft_printf("-%s\n", command->tokens[0]);
			ft_printf("minishell: %s: Permission denied\n", command->tokens[0]);
			exit(126);
			
		}
	}
	//else
		//ft_printf("%s : not exist\n", command->tokens[0]);
	//exit(0);
	else
	{
		//ft_printf("%s\n", command->tokens[0]);
		if (command->tokens[0][0] == '/' || (ft_strlen(command->tokens[0]) > 2 && command->tokens[0][0] == '.' && command->tokens[0][1] == '/'))
		{
			ft_printf("minishell: %s: No such file or directory\n", command->tokens[0]);
			exit(127);
		}
		path = ft_get_path();
		bins = ft_split(path, ':');
		//ft_printf("path : -%s-  bins : -%s-\n", path, *bins);
		if(!path || *path == '\0' || !bins)
		{
			ft_printf("minishell: %s: No such file or directory\n", command->tokens[0]);
			exit(127);
		}
		i = 0;
		while(bins[i])
		{
			path = ft_strjoin(bins[i], "/");
			file = ft_strjoin(path, command->tokens[0]);
			if (!stat(file, &path_stat))
			{
				envp = ft_get_envp();
				//ft_printf("%s : %s : %s", file, command->tokens[0], envp[0]);
				execve(file, command->tokens, envp);
				//ft_free_d_p(envp);
				ft_printf("minishell: %s: %s\n", command->tokens[0], strerror(errno));
				exit(126);
			}
			i++;
		}
		//ft_free_d_p(bins);
	}
	return (0);
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
