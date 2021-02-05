/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 22:39:14 by devza             #+#    #+#             */
/*   Updated: 2021/02/04 00:05:43 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_next_limit(char *line, int i)
{
    while (line[i] != '\0')
    {
        if (line[i] == ';')
        {
            g_token.limit = POIN_VER;
            return (i);
        }
        else
        {
            g_token.limit = 0;
            i++;
        }
    }
    return (i);
}

int     ft_next_space(char *line, int i)
{
    while (line[i] != '\0' && line[i] != ' ')
        i++;
    return (i);
}

void    ft_parse(char *line)
{
    int i;
    int start;
    int end;
    t_list new_token;

    i = 0;
    while (line[i] != '\0')
    {
        if (line[i] == ' ')
            i++;
        else
        {
            start = i;
            end = ft_next_space(line, i);
            g_token.command = ft_substr(line, start, end - start);
            ft_putstr_fd(g_token.command, 0);
            write(1,"-",1);
            start = end;
            end = ft_next_limit(line, end);


            i = end;
        }
    }
}

void    ft_prompt()
{
    char *line;

    ft_putstr_fd("\033[0;32m", 0);
    ft_putstr_fd("minishell 👽 > ", 0);
    ft_putstr_fd("\033[0m", 0);
	get_next_line(0, &line);
    if (line[0] == '*')
        exit (0);
    printf("you need to pars this 💩 : |%s|\n", line);
    ft_parse(line);
}

int     main()
{
    while (1)
    {
        ft_prompt();
    }
    
    return (0);
}
