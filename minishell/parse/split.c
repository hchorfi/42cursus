/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <anassif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:14:39 by anassif           #+#    #+#             */
/*   Updated: 2021/02/15 18:08:37 by anassif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	countt(char *s, char c)
{
	int i;
	int w;

	i = 0;
	w = 0;
	while (1)
	{
		if ((s[i] == c && i != 0 && s[i - 1] != c)
			|| (s[i] == '\0' && i > 0 && s[i - 1] != c))
			w++;
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (w);
}

static char	**ft_free(char **s, int j)
{
	while (j)
	{
		free(s[j--]);
	}
	free(s);
	return (NULL);
}

static int ft_count (const char *s, int l)
{
	int i;

	i = 0;
	while (i < l && s[i] != '\0')
	{
		i++;
	}
	return (i);
}

static int check_cots(const char *s, int l, int d)
{
	int i;
	int len;
	int n;

	len = ft_count(s + d, l) + d;
	i = d;
	n = 0;
	while (i < l)
	{
		if (s[i] == '"' && s[i - 1] != '\\')
			n++;
		i++;
	}
	if (n % 2 == 0)
		return (1);
	return (0);
}

void		remove_tabs_check(char *s, char c)
{
	int i = 0;
	while (s[i])
	{
		if (s[i] == c && s[i - 1] != '\\')
		{
			i++;
			while (s[i] == '\t' || s[i] == ' ')
				i++;
			if (s[i] == c)
				printf("bash: syntax error near unexpected token"), exit(1);
		}
		i++;
	}
}

char		**ft_split_pars(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	d;
	char	**str;
	char	*s1;

	if (!s)
		return (NULL);
	s1 = ft_strtrim(s, " ");
	s = ft_strdup(s1);
	if (!(str = (char **)malloc(sizeof(char *) * (countt((char *)s, c) + 1))))
		return (NULL);
	i = 0;
	d = 0;
	j = 0;
	int splited = 0;
	while (2)
	{
		if ((((s[i] == c && i != 0) || (s[i] == '\0' && i > 0)) && s[i - 1] != c) && s[i - 1] != '\\')
		{
			if (check_cots(s, i, d))
				{
					if (!(str[j++] = ft_substr((char *)s, d, i - d)))
						return (ft_free(str, j - 1));
					splited = 1;
				}
		}
		d = (splited == 1 ? i + 1 : d);
		splited = 0;
		if (s[i++] == '\0')
			break ;
	}
	str[j] = NULL;
	return (str);
}

// int main (int ac, char **av)
// {
// 	char **cmds;
// 	char **cmd;
// 	char **token;
// 	int i =0;
// 	int j=0;
// 	char *s= "echo \"fefwfwfs;efsfsefsef\" | ls -la ; ls -la | grep file ; cat file1 > file2 | pwd";
// 	//remove_tabs_check(s, ';');
// 	cmds = ft_split(s, ';');
// 	while (cmds[i])
// 	{
// 		printf("********cmd******\n%s\n", cmds[i]);
// 		cmd = ft_split(cmds[i], '|');
// 		j = 0;
// 		while (cmd[j])
// 			printf("------------%s\n", cmd[j++]);
// 		i++;
// 	}
	
	
// 	// j = 0;
// 	// i = 0;
// 	// printf("------1 by 1---------\n");
// 	// while (cmd[i])
// 	// {
// 	// 	token = ft_split(cmd[i], ' ');
// 	// 	i++;
// 	// }
// 	// i = 0;
// 	// while (token[i])
// 	// {
// 	// 	printf("|%s|\n", token[i]);
// 	// 	i++;
// 	// }
// 	return 0;
// }