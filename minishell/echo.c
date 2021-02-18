/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <anassif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 17:34:22 by anassif           #+#    #+#             */
/*   Updated: 2021/02/16 17:34:22 by anassif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static	int		is_quote(char c)
{
	if (c == '"' || c== '\'')
		return (1);
	return(0);
}

static void	ft_putnstr(char *str, int n)
{
	int		i;

	i = -1;
	if (n < 0)
	{
		while (str[++i] && i < (int)ft_strlen(str) + n)
			ft_putchar_fd(str[i], 1);
	}
	else
	{
		while (str[++i] && i < n)
			ft_putchar_fd(str[i], 1);
	}
}

static void		my_echo_2(char **s, int pos)
{
	int		firt_isquote;
	int		last_isquote;
	int		len;

	firt_isquote = is_quote(s[pos][0]);
	len = ft_strlen(s[pos]);
	last_isquote = is_quote(s[pos][len - 1]);
	if (last_isquote && firt_isquote)
		ft_putnstr(s[pos] + 1, -1);
	else if (last_isquote)
		ft_putnstr(s[pos], -1);
	else if (firt_isquote)
		ft_putstr_fd(s[pos] + 1, 1);
	else
		ft_putstr_fd(s[pos], 1);
	if (s[pos + 1])
		ft_putchar_fd(' ', 1);
}

static	int check_n(char *args)
{
	int i;

	i = 0;
	if (args[0] == '-')
		i++;
	else
		return (0);
	while(args[i])
	{
		if (args[i] == 'n')
			i++;
		else if (args[i] != '\0')
			return (0);
	}
	return (1);
}

int				ft_echo()
{
	int		i;
	int		n;

	n = 0;
	if (!g_command->tokens[0])
	{
		write(1, "\n", 1);
		return (1);
	}
	i = 1;
	while (g_command->tokens[i])
	{
		if (!(check_n(g_command->tokens[i])))
			break ;
		n = 1;
		i++;
	}
	while (g_command->tokens[i])
	{
		my_echo_2(g_command->tokens, i);
		if (!g_command->tokens[i + 1] && n == 0)
			ft_putchar_fd('\n', 1);
		i++;
	}
	return (1);
}


// int main()
// {
// 	char **s;
// 	s[0] = "-nnn";
// 	s[1] = "-nnnnnm";
// 	s[2] = "\'hell  '    ll  'rld\'";
// 	s[3] = "\"fuck off\"";
// 	s[4] = "-n";
// 	s[5] = NULL;
// 	my_echo(s);
// 	// printf("%d", check_n("-nnnn"));
// 	// printf("%d", check_n("-n"));
// 	// printf("%d", check_n("-nnnm"));
// 	return 0;
// }