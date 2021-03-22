/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:05:25 by hchorfi           #+#    #+#             */
/*   Updated: 2021/03/08 21:12:59 by hchorfi          ###   ########.fr       */
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
	if (!(envp = malloc(sizeof (char*) * list_len)))
		return (NULL);
	while (newlist)
	{
		envp[i] = newlist->content;
		newlist = newlist->next;
		i++;
	}
	return (envp);
}

void	ft_free_d_p(char **str)
{
	int		len;

	len = 0;
	while (*str)
	{
		free(*str);
		(*str)++;
	}
	free(str);
	
}

int		ft_exec_bin(void *cmd)
{
	int		pid;
	int		status;
	char	**bins;
	char	*path;
	char	*file;
	int		i;
	struct stat path_stat;
	char	**envp;
	g_command = (t_command *)cmd;

	if(!stat(g_command->tokens[0], &path_stat))
	{
		//ft_printf("%s : exist\n", g_command->tokens[0]);
		if (path_stat.st_mode & S_IFDIR)
		{
			ft_printf("minishell: %s: is a directory\n", g_command->tokens[0]);
			exit(126);
		}
		else
		{
			envp = ft_get_envp();
			if (execve(g_command->tokens[0], g_command->tokens, envp) == -1)
				ft_printf("minishell: %s: Permission denied\n", g_command->tokens[0]);
			exit(126);
		}
	}
	//else
		//ft_printf("%s : not exist\n", g_command->tokens[0]);
	//exit(0);
	else
	{
		path = ft_get_path();
		bins = ft_split(path, ':');
		//ft_printf("path : -%s-  bins : -%s-\n", path, *bins);
		if(!path || *path == '\0' || !bins)
		{
			ft_printf("minishell: %s: No such file or directory\n", g_command->tokens[0]);
			exit(127);
		}
		i = 0;
		while(bins[i])
		{
			path = ft_strjoin(bins[i], "/");
			file = ft_strjoin(path, g_command->tokens[0]);
			if (!stat(file, &path_stat))
			{
				envp = ft_get_envp();
				execve(file, g_command->tokens, envp);
				//ft_printf("minishell: %s: %s\n", g_command->tokens[0], strerror(errno));
				exit(126);
			}
			i++;
		}
	}
	ft_free_d_p(bins);
	return (0);
}
