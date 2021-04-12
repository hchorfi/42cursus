#include "../minishell.h"

int	check_special(char c, char cs, char *special, int *is_back)
{
	int	stoped;

	stoped = (*is_back && c == cs);
	if (!*special && (c == '\'' || c == '"') && !*is_back)
		*special = c;
	else if ((c == '\'' || (c == '"' && !*is_back)) && *special == c)
		*special = 0;
	if (*is_back)
		*is_back = 0;
	else if (c == '\\')
		*is_back = 1;
	return (c == cs && !*is_back && !*special
		&& !stoped);
}

void	free_split(char **sp)
{
	int		iter;

	iter = 0;
	while (sp[iter])
	{
		free(sp[iter]);
		iter++;
	}
	free(sp);
}

static int	count_word(const char *str, char c, int is_back)
{
	char	special_char;
	int		looked;
	int		count;
	int		iter;

	looked = 1;
	count = 0;
	special_char = 0;
	iter = 0;
	while (str[iter])
	{
		if (check_special(str[iter], c, &special_char, &is_back))
			looked = 1;
		if (looked)
		{
			looked = 0;
			count++;
			while (str[iter] && str[iter] == c)
				iter++;
			if (!str[iter])
				break ;
		}
		iter++;
	}
	return (count);
}

static int	*get_length_substrings(const char *str, int c, int wc, int is_back)
{
	int		*arr;
	int		iter;
	int		len;
	int		iter_arr;
	char	special;

	arr = malloc(sizeof(int) * wc);
	iter = 0;
	iter_arr = -1;
	special = 0;
	while (str[iter])
	{
		len = 0;
		while (str[iter] == c)
			iter++;
		while (!check_special(str[iter], c, &special, &is_back) && str[iter])
		{
			len++;
			iter++;
		}
		arr[++iter_arr] = len;
	}
	return (arr);
}

static char	*get_word(const char *str, int start, int len)
{
	char	*new_s;
	int		iter;

	new_s = malloc(sizeof(char) * (len + 1));
	iter = 0;
	while (iter < len)
	{
		new_s[iter] = str[start + iter];
		iter++;
	}
	new_s[iter] = 0;
	return (new_s);
}

char	**csplit(const char *s, char c)
{
	int		wc;
	int		*arr;
	int		iter;
	char	**sub_strs;
	int		iter_sub;

	if (!s)
		return (NULL);
	wc = count_word(s, c, 0);
	arr = get_length_substrings(s, c, wc, 0);
	sub_strs = malloc(sizeof(char *) * (wc + 1));
	iter = 0;
	iter_sub = 0;
	while (s[iter])
	{
		while (s[iter] == c)
			iter++;
		sub_strs[iter_sub] = get_word(s, iter, arr[iter_sub]);
		iter += arr[iter_sub];
		iter_sub++;
	}
	free(arr);
	sub_strs[wc] = NULL;
	return (sub_strs);
}