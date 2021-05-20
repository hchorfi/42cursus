/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 14:54:36 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/20 18:08:36 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

#define LEFT philo->ph_number - 1
#define RIGHT ((philo->ph_number - 1) + 1) % data->n_philos

typedef struct  s_data
{
    int             n_philos;
    int             max_ph_eat;
    int             ph_counter;
    pthread_mutex_t *f_mutex;
    pthread_t	    *thread;
}                   t_data;

typedef struct  s_philo
{
    int         ph_number;
    int         tt_die;
    int         tt_eat;
    int         tt_sleep;
    t_data      *data;
}               t_philo;

/*
** error.c
*/

int arg_count_err(void);

/*
** utils.c
*/

int	ft_atoi(const char *str);

#endif
