/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <anassif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:14:39 by anassif           #+#    #+#             */
/*   Updated: 2021/03/11 16:26:21 by anassif          ###   ########.fr       */
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

int			is_escaped(char *s, int j)
{
	int i = 0;
	j--;
	while (j >= 0 && s[j] == '\\')
	{
		j--;
		i++;
	}
	return (i % 2);
}


static int check_cots(const char *s, int l, int d)
{
	int i;
	int len;
	int n;
	int s_quote = 0;

	len = ft_count(s + d, l) + d;
	i = d;
	n = 0;
	if ((s[i] == '"' || s[i] == '\'') && !(is_escaped((char *)s, i)))
		n++;
	i++;
	while (i < l)
	{
		if ((s[i] == '"' || s[i] == '\'') && !(is_escaped((char *)s, i)))
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

char    *ft_stock(char *line, char *buff, int i)
{
    int j =0; char *newline; int len=0;
    len = (line ? ft_strlen(line) : 0);
    newline = malloc(len + i + 1);
    while (j < len)
        newline[j] = line[j], j++;
    if (line)
        free(line);
    while (j < len +i)
        newline[j] = buff[j - len], j++;
    newline[j] = '\0';
    return(newline);
}

//k here is the index after $

char		*ft_put_variable(char *str, int k, int j)
{
	char *var;
	int i = 0;

	k++;
	var = (char *)malloc(j - k + 2);
	while (i <= j - k)
	{
		var[i] = str[k + i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

char		*ft_variable_value(char *var)
{
	t_list  *newlist;
    char    *new_var;
    char    *old_var;
    char    *tmp_str;
    int     tmp_len;
    int     len;
    int     i;

    newlist = g_data.env_var;
    new_var = var;
    i = 1;
    while (newlist)
    {
        if ((tmp_str = ft_strchr(newlist->content, '=')))
        {
            tmp_len = ft_strlen(tmp_str);
            len = ft_strlen(newlist->content);
            old_var = ft_substr(newlist->content, 0, len - tmp_len);
        }
        else
        {
            old_var = newlist->content;
            len = ft_strlen(old_var);
        }
        if (ft_strncmp(old_var, new_var, len) == 0)
        {   
            if (ft_strchr(newlist->content, '='))
				return (ft_strchr(newlist->content, '=') + 1);
        }
        newlist = newlist->next;
        i++;
    }
	
	return ("");
}

char	*ft_replace_variable(char *str, char *value, int k, int j)
{
	int i = 0;
	char *ptr;
	int value_len = ft_strlen(value);
	ptr = (char *)malloc(value_len + ft_strlen(str) - j + k + 1);
	while (i < k)
	{
		ptr[i] = str[i];
		i++;
	}
	int x = 0;
	while (x < value_len)
	{
		ptr[i + x] = value[x];
		x++;
	}
	i = i + x;
	// ft_putchar_fd(ptr[i - 1],1);
	// ft_putstr_fd("\n", 1);
	j++;
	while (str[j])
	{
		// if (str[j] == '"')
		// 	break ;
		ptr[i] = str[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	// ft_putstr_fd(ptr, 1);
	// ft_putstr_fd("\n", 1);
	return (ptr);
}
// start is index of starting the search
//k is you found the $
//j is going to be where the variable name finishes
//i is the end of the string you ll search on
// var is the variable after $ if it meets requirements ' ' or '\0'

char		*ft_get_variables(char *str, int start, int i)
{
	char *var;
	int j;
	j = start;
	int k = 0;
	int s_quote = 0;
	char *value;
	// ft_putstr_fd(str, 1);
	// ft_putstr_fd("\n", 1);
	while (j < i)
	{
		if (str[j] == '\'')
		{
			if (s_quote == 0)
				s_quote = 1;
			else
				s_quote = 0;
			j++;
		}
		if (str[j] == '$' && s_quote == 0 && !(is_escaped(str, i)))
		{	
			k = j;
			while (++j < i)
			{
				if (str[j] == ' ' || str[j] == '"' || str[j] == '\'' || str[j] == '/' || str[j] == '$' || str[j] == ':' || str[j] == '=')
					break ;
			}
			break ;
		}
		j++;
	}
	j--;
	var = ft_put_variable(str, k, j);

	value = ft_variable_value(var);
	str = ft_replace_variable(str, value, k, j);
	return (str);
}

char		*get_other_variables(char *str)
{	
	int i = 0;
	int dollar = 0;
	int s_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !(is_escaped((char *)str, i)))
		{
			if (s_quote == 0)
				s_quote = 1;
			else
				s_quote = 0;
		}
		if (str[i] == '$' && s_quote == 0 && !(is_escaped(str, i)))
			dollar++;
		i++;
	}
	i = 0;
	while (i < dollar)
	{
		str = ft_get_variables(str, 0, ft_strlen(str));
		i++;
	}
	return (str);
}

void		fill_with(char *s, int  start, int len, char c)
{
	int i;

	i = 0;
	while (i < len)
	{
		s[start + i] = c;
		i++;
	}
}

char		*ft_remove_slashes(char *str, int start, int end)
{
	int i = start;
	int count = 0;
	int len = 0;
	char *back;
	int j;
	while (i < end)
	{
		if (str[i] == '\\')
			count++;
		else
		{
			len += count / 2 + 1;
			count = 0;
		}
		i++;
	}
	if (count)
		len += count / 2;
	back = malloc(sizeof(char) * (len  + 1));
	i = start;
	j = 0;
	count = 0;
	while (i < end)
	{
		if (str[i] == '\\')
			count++;
		else
		{
			fill_with(back, j, count / 2, '\\');
			j += count / 2;
			count = 0;
			back[j] = str[i];
			j++;
		}
		i++;
	}
	if (count)
		fill_with(back, j, count / 2, '\\');
	j += count / 2;
	back[j] = '\0';
	return (back);
}

char		*ft_remove_slashes_2(char *str, int start, int end)
{
	int i = start;
	int count = 0;
	int len = 0;
	char *back;
	int j;
	while (i < end)
	{
		if (str[i] == '\\')
			count++;
		else
		{
			if ((str[i] == '$' || str[i] == '"') && (count % 2))
			{
				len += (count / 2) + 1;
				count = 0;
			}
			else
			{
				count++;
				len += count / 2 + 1;
				count = 0;
			}
		}
		i++;
	}
	if (count)
		len += count / 2;
	back = malloc(sizeof(char) * (len  + 1));
	i = start;
	j = 0;
	count = 0;
	while (i < end)
	{
		if (str[i] == '\\')
			count++;
		else
		{
			if ((str[i] == '$' || str[i] == '"') && (count % 2))
			{
				fill_with(back, j, (count / 2), '\\');
				j += count / 2;
				count = 0;
				back[j] = str[i];
				j++;
			}
			else
			{
				count++;
				fill_with(back, j, count / 2, '\\');
				j += count / 2;
				count = 0;
				back[j] = str[i];
				j++;
			}
		}
		i++;
	}
	if (count)
		fill_with(back, j, count / 2, '\\');
	j += count / 2;
	back[j] = '\0';
	return (back);
}

char		*remove_all_quotes(char *str)
{
	int s_quote = 0;
	int d_quote = 0;
	int start = 0;
	int i = 0;
	char *ptr;
	char *final = NULL;
	char *s;
	int trim = 0;
	int hh = 0;
	ptr = ft_strdup("");
	while(str[i])
	{
		if (str[i] == '\'' && s_quote == 0 && d_quote == 0 && !(is_escaped(str, i)))
		{
			s_quote = 1;
			s = ft_remove_slashes(str, start, i);
			ptr = ft_stock(ptr, s, ft_strlen(s));
			start = i + 1;
			trim = 1; 
			i++;
		}
		if (str[i] == '\'' && s_quote == 1 /*&& !(is_escaped(str, i))*/)
		{
			s = ft_substr(str, start, i - start);
			ptr = ft_stock(ptr, s, i - start);
			start = i + 1;
			//i++;
			s_quote = 0;
		}
		if (str[i] == '"' && d_quote == 0 && s_quote == 0 && !(is_escaped(str, i)))
		{
			d_quote = 1;
			s = ft_remove_slashes(str, start, i);
			ptr = ft_stock(ptr, s, ft_strlen(s));
			start = i + 1;
			trim = 1;
			i++;
		}
		if (str[i] == '"' && d_quote == 1 && str[i] != '\0' && !(is_escaped(str, i)))
		{
			// int j;
			// j = start;
		 	s = ft_remove_slashes_2(str, start, i);
			// ft_putstr_fd(s, 1);
			// ft_putstr_fd("\n", 1);
			ptr = ft_stock(ptr, s, ft_strlen(s));
			start = i + 1;
			d_quote = 0;
		}
		if (str[i] != '\0')	
			i++;
		if (str[i] == '\0')
		{
			s = ft_remove_slashes(str, start, i);
			ptr = ft_stock(ptr, s, ft_strlen(s));
			break ;
		}
	}
	if (trim == 0)
		ptr = ft_strtrim(ptr, " ");
	return(ptr);
}

char		**ft_split_pars(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	d;
	char	**str;

	if (!s)
		return (NULL);
	if (!s)
	s = ft_strtrim(s, " ");
	if (!(str = (char **)malloc(sizeof(char *) * (countt((char *)s, c) + 1))))
		return (NULL);
	i = 0;
	d = 0;
	j = 0;
	int splited = 0;
	while (2)
	{
		if ((((s[i] == c && i != 0) || (s[i] == '\0' && i > 0)) && s[i - 1] != c) && !(is_escaped((char *)s, i)))
		{
			// if (check_cots(s, i, d))
			// 	{
					if (!(str[j++] = ft_substr((char *)s, d, i - d)))
						return (ft_free(str, j - 1));
					splited = 1;
				// }
		}
		d = (splited == 1 ? i + 1 : d); 
		splited = 0;
		if (s[i++] == '\0')
			break ;
	}
	str[j] = NULL;
	// if (c == ' ')
	// {
	// 	j = 0;
	// 	while (str[j])
	// 	{
	// 		str[j] = get_other_variables(str[j]);
	// 		// ft_putstr_fd(str[j], 1);
	// 		// ft_putstr_fd("\n", 1);
	// 		str[j] = remove_all_quotes(str[j]);
	// 		j++;
	// 	}
	// 	// j = 0;
	// 	// while(str[j])
	// 	// {
	// 	// 	ft_putstr_fd(str[j], 1);
	// 	// 	ft_putstr_fd("\n", 1);
	// 	// 	j++;
	// 	// }
	// }
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