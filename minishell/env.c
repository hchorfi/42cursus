/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 14:43:25 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/03 17:33:10 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_stock_ret(void)
{
	char	*str;
	t_list	*env_list;
	int		exist;
	char	*tmp_free;
	char	*tmp_free2;

	//exist = 0;
	env_list = g_data.env_var;
	while (env_list)
	{
		if (*(char *)(env_list)->content == '?')
		{
			//ft_printf("ok\n");
			tmp_free2 = ft_itoa(g_data.ret);
			str = ft_strjoin("?=", tmp_free2);
			tmp_free = env_list->content;
			//ft_printf("bfor : %p |%s|\n",tmp_free, tmp_free);
			env_list->content = str;
			//ft_printf("after : %p |%s|\n",env_list->content, env_list->content);
			free(tmp_free2);
			free(tmp_free);
			tmp_free = NULL;
			ft_printf("%s\n", tmp_free);
			break;
			//exist = 1;
		}
		env_list = env_list->next;
	}
	// if (!exist)
	// 	ft_lstadd_back(&g_data.env_var, ft_lstnew(str));
}

char	**ft_get_envp(void)
{
	int		list_len;
	char	**envp;
	t_list	*newlist;
	int		i;

	list_len = ft_lstsize(g_data.env_var);
	newlist = g_data.env_var;
	i = 0;
	envp = malloc(sizeof (char *) * (list_len + 1));
	if (!envp)
		return (NULL);
	while (newlist)
	{
		envp[i] = newlist->content;
		newlist = newlist->next;
		i++;
	}
	envp[list_len] = NULL;
	return (envp);
}

void	ft_stock_envp(char **envp)
{
	int		i;
	char	*str;
	char	*tmp_free;
	
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
	ft_lstadd_back(&g_data.env_var, ft_lstnew(ft_strdup("?=0")));
}

int	ft_env(t_command *command)
{
	t_list	*newlist;

	newlist = g_data.env_var;
	if (command->n_tokens == 1)
	{
		while (newlist)
		{
			if (ft_strchr(newlist->content, '=')
				&& *(char *)(newlist)->content != '?')
				ft_putstrs_fd(newlist->content, "\n", NULL, NULL);
			newlist = newlist->next;
		}
	}
	return (g_data.ret = 0);
}
