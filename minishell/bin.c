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
			path = ft_strrchr(newlist->content, '=');
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
	i=0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i],1);
		write(1, "\n", 1);
		i++;
	}
	return (envp);
}

int		ft_check_bin()
{
	int		pid;
	int		status;
	char	**bins;
	char	*path;
	char	*file;
	int		i;
	struct stat path_stat;
	char	**envp;
	
	path = ft_get_path();
	bins = ft_split(path, ':');
	i = 0;
	while(bins[i])
	{
		path = ft_strjoin(bins[i], "/");
		file = ft_strjoin(path, g_command.tokens[0]);
		if (!stat(file, &path_stat))
		{
			pid = fork();
			if (pid == 0)
			{
				envp = ft_get_envp();
			    execve(file, g_command.tokens,NULL);
			}
			else
			{
				wait(&status);
				return (0);
			}
		}
		i++;
	}
	return (0);
}