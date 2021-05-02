/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:14:39 by anassif           #+#    #+#             */
/*   Updated: 2021/05/02 00:11:37 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_escaped(char *s, int j)
{
	int	i;

	i = 0;
	j--;
	while (j >= 0 && s[j] == '\\')
	{
		j--;
		i++;
	}
	return (i % 2);
}

int	chec_before(char *s, int i, char c)
{
	if (s[i - 1] == c && !is_escaped(s, i - 1))
		return (0);
	return (1);
}

static int	countt(char *s, char c)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	while (1)
	{
		if (((s[i] == c && i != 0) || (s[i] == '\0' && i > 0))
			&& chec_before(s, i, c) && !is_escaped(s, i))
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

static int	ft_count(const char *s, int l)
{
	int	i;

	i = 0;
	while (i < l && s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	check_char(char c)
{
	if (c == ' ' || c == '"' || c == '\'' || c == '/' || c == '$' || c == ':'
		|| c == '=' || c == '|' || c == ',' || c == '\\' || c == '\''
		|| c == '"' || c == '[' || c == ']' || c == '@')
		return (1);
	return (0);
}

static int	check_cots(char *s, int d_quote, int s_quote)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' && s_quote == 0 && d_quote == 0 && !(is_escaped(s, i)))
		{
			s_quote = 1;
			i++;
		}
		if (s[i] == '\'' && s_quote == 1)
			s_quote = 0;
		if (s[i] == '"' && d_quote == 0 && s_quote == 0 && !(is_escaped(s, i)))
		{
			d_quote = 1;
			i++;
		}
		if (s[i] == '"' && d_quote == 1 && s[i] != '\0' && !(is_escaped(s, i)))
			d_quote = 0;
		if (s[i] != '\0')
			i++;
	}
	if (s_quote == 0 && d_quote == 0)
		return (1);
	return (0);
}

int	remove_tabs_check(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c && s[i - 1] != '\\')
		{
			i++;
			while (s[i] == '\t' || s[i] == ' ')
				i++;
			if (s[i] == c)
				return (1);
		}
		if (s[i] != '\0')
			i++;
	}
	return (0);
}

char	*ft_stock(char *line, char *buff, int i)
{
	char	*newline;
	int		len;
	int		j;

	j = 0;
	len = 0;
	if (line)
		len = ft_strlen(line);
	newline = (char *)malloc(len + i + 1);
	while (j < len)
	{
		newline[j] = line[j];
		j++;
	}
	if (line)
		free(line);
	while (j < len + i)
	{
		newline[j] = buff[j - len];
		j++;
	}
	newline[j] = '\0';
	return (newline);
}

char	*ft_put_variable(char *str, int k, int j)
{
	char	*var;
	int		i;

	i = 0;
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

char	*ft_variable_value(char *var)
{
	t_list	*newlist;
	char	*old_var;
	char	*tmp_str;
	int		tmp_len;
	int		len;

	newlist = g_data.env_var;
	while (newlist)
	{
		old_var = ft_get_oldvar(newlist->content);
		if (ft_strcmp(old_var, var) == 0)
		{
			if (ft_strchr(newlist->content, '='))
			{
				free(old_var);
				return (ft_strchr(newlist->content, '=') + 1);
			}
		}
		ft_free_exist(old_var, newlist->content, '=');
		newlist = newlist->next;
	}
	return ("");
}

int	ft_ch_do(int i, int c, char *s)
{
	while (s[i])
	{
		if (s[i] == '\\')
			c++;
		i++;
	}
	return (c);
}

char	*ft_check_dollar_slash(char	*s, int i, int c)
{
	char	*value;

	value = (char *)malloc(ft_strlen(s) + ft_ch_do(0, 0, s) + 1);
	while (s[i])
	{
		if (s[i] == '\\')
		{
			value[c] = '\\';
			c++;
			value[c] = '\\';
			c++;
			i++;
		}
		else
		{
			value[c] = s[i];
			if (s[i] != '\0')
			{
				i++;
				c++;
			}
		}	
	}
	value[c] = '\0';
	return (value);
}

int	ft_rep_var_2(int value_len, char *value, char *ptr, int *i)
{
	int	x;

	x = 0;
	while (x < value_len)
	{
		ptr[*i + x] = value[x];
		x++;
	}
	return (x);
}

char	*ft_replace_variable(char *str, char *value, int k, int j)
{
	int		i;
	char	*ptr;
	int		value_len;

	i = 0;
	value_len = ft_strlen(value);
	ptr = (char *)malloc(value_len + ft_strlen(str) - j + k + 1);
	while (i < k)
	{
		ptr[i] = str[i];
		i++;
	}
	i = i + ft_rep_var_2(value_len, value, ptr, &i);
	j++;
	while (str[j])
	{
		ptr[i] = str[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	ft_get_var3(int *s_quote, int *d_quote, int *j, char *str)
{
	if (str[*j] == '\"' && !(is_escaped(str, *j)))
	{
		if (*d_quote == 0)
			*d_quote = 1;
		else
			*d_quote = 0;
		(*j)++;
	}
	if (str[*j] == '\'' && !(is_escaped(str, *j)) && *d_quote == 0)
	{
		if (*s_quote == 0)
			*s_quote = 1;
		else
			*s_quote = 0;
		(*j)++;
	}
}

int	ft_get_var2(int j, char *str, int *k, int i)
{
	int		s_quote;
	int		d_quote;

	s_quote = 0;
	d_quote = 0;
	while (j < i)
	{
		ft_get_var3(&s_quote, &d_quote, &j, str);
		if (str[j] == '$' && s_quote == 0 && !(is_escaped(str, j)))
		{	
			*k = j;
			while (++j < i)
			{
				if (check_char(str[j]))
					break ;
			}
			break ;
		}
		j++;
	}
	return (j);
}

char	*ft_get_variables(char *str, int start, int i)
{
	char	*var;
	int		j;
	int		k;
	char	*value;

	k = 0;
	j = ft_get_var2(start, str, &k, i) - 1;
	if (k == j)
	{
		str = ft_replace_variable(str, "$", k, j);
		return (str);
	}
	var = ft_put_variable(str, k, j);
	value = ft_variable_value(var);
	free(var);
	value = ft_check_dollar_slash(value, 0, 0);
	str = ft_replace_variable(str, value, k, j);
	free(value);
	return (str);
}

int	get_other_var2(char *str, int i, int d_quote, int s_quote)
{
	int	dollar;

	dollar = 0;
	while (str[i])
	{
		if (str[i] == '\"' && !(is_escaped(str, i++)))
		{
			if (d_quote == 0)
				d_quote = 1;
			else
				d_quote = 0;
		}
		if (str[i] == '\'' && !(is_escaped((char *)str, i)) && d_quote == 0)
		{
			if (s_quote == 0)
				s_quote = 1;
			else
				s_quote = 0;
		}
		if (str[i] == '$' && s_quote == 0 && !(is_escaped(str, i)))
			dollar++;
		if (str[i] != '\0')
			i++;
	}
	return (dollar);
}

char	*get_other_variables(char *str)
{	
	int		i;
	int		dollar;
	char	*tmp_free;

	dollar = get_other_var2(str, 0, 0, 0);
	i = 0;
	while (i < dollar)
	{
		str = ft_get_variables(str, 0, ft_strlen(str));
		i++;
	}
	if (!str || *str == '\0')
		return (str);
	else
	{	
		tmp_free = str;
		str = ft_strtrim(str, " ");
		if (i > 0)
			free(tmp_free);
		return (str);
	}
}

void	fill_with(char *s, int start, int len, char c)
{
	int	i;

	i = 0;
	while (i < len)
	{
		s[start + i] = c;
		i++;
	}
}

int	ft_remove_slashes3(int i, char *str, int end)
{
	int	len;
	int	count;

	len = 0;
	count = 0;
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
	return (len);
}

void	ft_remove_slashes4(char *str, char **back, int end, int i)
{
	int count;
	int	j;

	count = 0;
	j = 0;
	while (i < end)
	{
		if (str[i] == '\\')
			count++;
		else
		{
			fill_with(*back, j, count / 2, '\\');
			j += count / 2;
			count = 0;
			(*back)[j] = str[i];
			j++;
		}
		i++;
	}
	if (count)
		fill_with(*back, j, count / 2, '\\');
	j += count / 2;
	(*back)[j] = '\0';
}

char	*ft_remove_slashes(char *str, int start, int end)
{
	int len;
	char *back;

	len = ft_remove_slashes3(start, str, end);
	back = malloc(sizeof(char) * (len  + 1));
	ft_remove_slashes4(str, &back, end, start);
	return (back);
}

char	*ft_remove_slashes_2(char *str, int start, int end)
{
	int i;
	int count;
	int len;
	char *back;
	int j;
	count = 0;
	len = 0;
	i = start;
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
char	*remove_all_quotes(char *str)
{
	int s_quote = 0;
	int d_quote = 0;
	int start = 0;
	int i = 0;
	char *ptr;
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
			free(s);
			i++;
		}
		if (str[i] == '\'' && s_quote == 1)
		{
			s = ft_substr(str, start, i - start);
			ptr = ft_stock(ptr, s, i - start);
			start = i + 1;
			free(s);
			s_quote = 0;
		}
		if (str[i] == '"' && d_quote == 0 && s_quote == 0 && !(is_escaped(str, i)))
		{
			d_quote = 1;
			s = ft_remove_slashes(str, start, i);
			ptr = ft_stock(ptr, s, ft_strlen(s));
			start = i + 1;
			trim = 1;
			free(s);
			i++;
		}
		if (str[i] == '"' && d_quote == 1 && str[i] != '\0' && !(is_escaped(str, i)))
		{
		 	s = ft_remove_slashes_2(str, start, i);
			ptr = ft_stock(ptr, s, ft_strlen(s));
			start = i + 1;
			d_quote = 0;
			free(s);
		}
		if (str[i] != '\0')	
			i++;
		if (str[i] == '\0')
		{
			s = ft_remove_slashes(str, start, i);
			ptr = ft_stock(ptr, s, ft_strlen(s));
			free(s);
			break ;
		}
	}
	return(ptr);
}

void	init_3params(int *i, int *j, int *d)
{
	*i = 0;
	*j = 0;
	*d = 0;
}

int	my_ternary(int splited, int i, int d)
{
	if (splited == 1)
		return (i + 1);
	return (d);
}

char	**ft_split_pars(char *s, char c)
{
	int	i;
	int	j;
	int	d;
	char	**str;
	char	*tmp_free;

	if (s != NULL)
		s = ft_strtrim(s, " ");
	str = (char **)malloc(sizeof(char *) * (countt(s, c) + 1));
	init_3params(&i, &j, &d);
	int splited = 0;
	while (2)
	{
		if (((s[i] == c && i != 0) || (s[i] == '\0' && i > 0)) && chec_before(s, i, c) && !is_escaped(s, i))
		{
			tmp_free = ft_substr(s, d, i - d);
			if (check_cots(tmp_free, 0, 0))
			{
				str[j++] = ft_substr(s, d, i - d);
				splited = 1;
			}
			free(tmp_free);
		}
		d = my_ternary(splited, i, d);
		splited = 0;
		if (s[i++] == '\0')
			break ;
	}
	str[j] = NULL;
	if (s)
		free (s);
	return (str);
}