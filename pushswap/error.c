/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 13:58:30 by hchorfi           #+#    #+#             */
/*   Updated: 2021/04/06 13:59:33 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int ft_check_error(int argc, char **argv)
{
    int i;
    int j;

    i = 1;
    while (argv[i])
    {
        j = 0;
        if (argv[i][j] == '-')
            j++;
        while (argv[i][j] != '\0')
        {
            if (!ft_isdigit(argv[i][j]))
                return (1);
            else
                j++;
        }
        i++;
    }
    argc--;
    while (argc >= 1)
    {
        j = argc;
        while (j >= 1)
        {
            if (!strcmp(argv[argc], argv[j - 1]))
                return (1);
            else
                j--;
        }
        argc--;
    }
    return (0);
}
