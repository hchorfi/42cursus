/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:05:25 by hchorfi           #+#    #+#             */
/*   Updated: 2021/03/31 17:37:38 by hchorfi          ###   ########.fr       */
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

char	**ft_get_envp()
{
	int		list_len;
	char	**envp;
	t_list	*newlist;
	int		i;

	list_len = ft_lstsize(g_data.env_var);
	newlist = g_data.env_var;
	i = 0;
	if (!(envp = malloc(sizeof (char*) * list_len + 1)))
		return (NULL);
	while (newlist)
	{
		envp[i] = newlist->content;
		newlist = newlist->next;
		i++;
	}
	//envp[i] = NULL;
	return (envp);
}

void	ft_free_d_p(char **str)
{
	int		len;

	len = 0;
	while (str[len])
		len++;
	while (len >= 0)
	{
		free(str[len]);
		len--;
	}
	free(str);
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
			envp = ft_get_envp();
			execve(command->tokens[0], command->tokens, envp);
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
				execve(file, command->tokens, NULL);
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
