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

#include "get_next_line.h"
int main()
{
    char *line;
    while (1)
    {
        write(1, "minishell 👽 > ", 18);
	    get_next_line(0, &line);
        if (line[0] == '*')
            exit (0);
        printf("you need to pars this 💩 : |%s|\n", line);
    }
}
