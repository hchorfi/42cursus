/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 16:52:19 by hchorfi           #+#    #+#             */
/*   Updated: 2020/12/14 16:52:20 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

int     main()
{
    //char *str1= "abc";
    //char *str2= "abd";
    char *dst = malloc(10 * sizeof (char));
    //printf("*%d*\n", strcmp("124","120"));
    //printf("*%d*\n", ft_strcmp("124","120"));
    //printf("*%s*\n", strcpy(dst,"13313213132132132313"));
    //printf("*%s*\n", strcpy(dst,"1"));
    //ssize_t l = ft_write(1, "hamza", 5);
    char *s = "12345";
    //char *tst_read = malloc(10 * sizeof (char));
   // if (ft_write(1, "NULL", 14) == -1)
    //    printf("%s: ", strerror(errno));
   // ssize_t l = ft_read(1, s, 5);
    printf("*%d*\n", strcmp("tesa", "tesT"));
    printf("*%d*", ft_strcmp("tesa", "tesT"));

    return 0;
}
