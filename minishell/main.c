/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 22:39:14 by devza             #+#    #+#             */
/*   Updated: 2021/02/08 18:42:50 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_exec()
{   
    int pid;
    int status;
    pid = fork();
    if (pid == 0)
        execve(ft_strjoin("/bin/", g_token.arguments[0]), g_token.arguments, NULL);
    else
        wait(&status);
    printf("okokokokok");
    return (1);
}

void    ft_parse(char *line)
{
    int i=0;
    g_token.arguments = ft_split(line, ' ');
}

int    ft_prompt()
{
    char *line;

    ft_putstr_fd("\033[0;32m", 1);
    ft_putstr_fd("minishell 👽 > ", 1);
    ft_putstr_fd("\033[0m", 1);
	get_next_line(0, &line);
    ft_parse(line);
    return 1;
}

int     main()
{
    while (1)
    {
        ft_prompt();
        ft_exec();
        ft_putstr_fd("...\n",1);
    }

    return (0);
}
