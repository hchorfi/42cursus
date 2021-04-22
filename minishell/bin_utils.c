#include "minishell.h"

void	ft_exec_error(int error, char *token)
{
	ft_putstr_fd("minishell: ", 2);
	if (error == 1)
	{
		ft_putstrs_fd(token, ": command not found\n", NULL, NULL, NULL);
		exit(127);
	}
	else if (error == 2)
	{
		ft_putstrs_fd(token, ": Is a directory\n", NULL, NULL, NULL);
		exit(126);
	}
	else if (error == 3)
	{
		ft_putstrs_fd(token, ": Permission denied\n", NULL, NULL, NULL);
		exit(126);
	}
	else if (error == 4)
	{
		ft_putstrs_fd(token, ": No such file or directory\n", NULL, NULL, NULL);
		exit(127);
	}
}

void	ft_dup_in_out(int dup, int in, int out)
{
	if (dup == 0 && in > 0 && in < 1024)
	{
		dup2(in, 0);
		close(in);
	}
	else
		dup2(g_data.fdd, 0);
	if (dup == 1 && out > 1 && out < 1024)
	{
		dup2(out, 1);
		close(out);
	}
}

char	*ft_get_path(void)
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