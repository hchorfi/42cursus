/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 14:54:36 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/18 18:38:00 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct  s_ph_data
{
    int ph_number;
    int tt_die;
    int tt_eat;
    int tt_sleep;
}               t_ph_data;

typedef struct  s_data
{
    int n_philos;
    int max_ph_eat;
}               t_data;

/*
** error.c
*/

int arg_count_err(void);

/*
** utils.c
*/

int	ft_atoi(const char *str);

#endif
