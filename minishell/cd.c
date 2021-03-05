/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 17:51:27 by hchorfi           #+#    #+#             */
/*   Updated: 2021/03/05 23:45:45 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_change_oldpwd(char *val)
{

	char	*tmp;
	t_list	*newlist;

	newlist = g_data.env_var;
	while (newlist)
	{
		tmp = ft_substr(newlist->content, 0, 7);
		if (!ft_strncmp(tmp, "OLDPWD=", 8))
		{
			newlist->content = ft_strjoin("OLDPWD=", val);
			free(tmp);
			return 0;
		}
		else
			newlist = newlist->next;
		free (tmp);
	}
	return 0;
}

int		ft_change_pwd(char *val)
{

	char	*tmp;
	t_list	*newlist;

	newlist = g_data.env_var;
	while (newlist)
	{
		tmp = ft_substr(newlist->content, 0, 4);
		if (!ft_strncmp(tmp, "PWD=", 5) )
		{
			newlist->content = ft_strjoin("PWD=", val);
			free(tmp);
			return 0;
		}
		else
			newlist = newlist->next;
		free (tmp);
	}
	return 0;
}

char	*ft_get_home(void)
{
	char	*tmp;
	char	*home;
	t_list	*newlist;

	newlist = g_data.env_var;
	while (newlist)
	{
		tmp = ft_substr(newlist->content, 0, 5);
		if (!ft_strncmp(tmp, "HOME=", 6))
		{
			free(tmp);
			return ((char *)newlist->content + 5);
		}
		else
			newlist = newlist->next;
		free (tmp);
	}
	ft_printf("minishell: cd: HOME not set\n");
	return (0);
}

int		ft_cd()
{
	char 	pwd[PATH_MAX];
	char	oldpwd[PATH_MAX];
	char	*val;
	getcwd(oldpwd, PATH_MAX);
	if (g_command->tokens[2])
	{
		ft_printf("minishell: cd: too many arguments\n");
		return (g_data.ret = 1);
	}
	if (!(val = g_command->tokens[1]))
	{	
		val = ft_get_home();
		if (*val == 0)
		{
			g_data.ret = 0;
			return (0);
		}
	}
	if (!chdir(val))
	{
		getcwd(pwd, PATH_MAX);
		ft_change_pwd(pwd);
		ft_change_oldpwd(oldpwd);
		g_data.ret = 0;
		return (0);
	}
	else
	{
		ft_printf("minishell: %s: No such file or directory\n", val);
		return (g_data.ret = 1);
	}
}
