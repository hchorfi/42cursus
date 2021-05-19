/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 14:52:14 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/19 23:35:53 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int mail = 0;

void	ft_init(int argc, char **argv, t_data *data, t_ph_data *ph_data)
{
	int i;

	i = 0;
	data->n_philos = ft_atoi(argv[1]);
	if (argc == 6)
		data->max_ph_eat = ft_atoi(argv[5]);
	else
		data->max_ph_eat = -1;
	while (i < data->n_philos)
	{
		ph_data[i].ph_number = i + 1;
		ph_data[i].tt_die = ft_atoi(argv[2]);
		ph_data[i].tt_eat = ft_atoi(argv[3]);
		ph_data[i].tt_sleep = ft_atoi(argv[4]);
		pthread_mutex_init(&(data->f_mutex)[i], NULL);
		i++;
	}
}

void	ft_print_philo_data(t_ph_data *ph_data, t_data *data)
{
	int i;

	i = 0;
	printf("%d philosopher on table\n", data->n_philos);
	if (data->max_ph_eat != -1)
		printf("each philosopher should eat max %d times\n", data->max_ph_eat);
	printf("**************\n");
	while (i < data->n_philos)
	{
		printf("%d philo number %d \n", i, ph_data[i].ph_number);
		printf("----------------\n");
		printf("time_to_die : %d\n", ph_data[i].tt_die);
		printf("time_to_eat : %d\n", ph_data[i].tt_eat);
		printf("time_to_sleep : %d\n\n", ph_data[i].tt_sleep);
		i++;
	}
}

void	ft_clear(t_ph_data *ph_data, t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&(data->f_mutex)[i]);
		i++;
	}
	free(ph_data);
	free(data->thread);
}

void	*ft_routine(void *v_ph_data)
{
	t_data *data;
	t_ph_data *ph_data;
	
	//n_data = (t_data *)data;
	ph_data = (t_ph_data *)v_ph_data;
	data = ph_data->data;
	//printf("%p\n", &data->f_mutex[0]);
	pthread_mutex_lock(&(ph_data->data->f_mutex)[0]);
	mail++;
	pthread_mutex_unlock(&(data->f_mutex)[0]);
	// pthread_mutex_lock(&ph_data->data->f_mutex[ph_data->ph_number - 1]);
	// printf("philo %d take a fork\n", ph_data->ph_number);
	// pthread_mutex_lock(&ph_data->data->f_mutex[(ph_data->ph_number - 1) % ph_data->data->n_philos]);
	// printf("philo %d take a fork\n", ph_data->ph_number);
	// printf("philo %d eating\n", ph_data->ph_number);
	// sleep(2);
	// pthread_mutex_unlock(&ph_data->data->f_mutex[ph_data->ph_number - 1]);
	// pthread_mutex_unlock(&ph_data->data->f_mutex[(ph_data->ph_number - 1) % ph_data->data->n_philos]);
	return ((void*)0);
}

void	ft_thread(t_ph_data *ph_data, t_data *data)
{
	int i;

	i = 0;
	while (i < data->n_philos)
	{
		//data->ph_counter = i;
		pthread_create(&data->thread[i], NULL, &ft_routine, ph_data);
		//printf("thread %d created\n", i);
		ph_data++;
		i++;
	}
	i = 0;
	while (i < data->n_philos)
	{
		pthread_join(data->thread[i], NULL);
		//printf("thread %d finish his job\n", i);		
		i++;
	}
}

int main(int argc, char **argv)
{
	t_data		data;
	t_ph_data	*ph_data;

	if (argc == 5 || argc == 6)
	{
		ph_data = malloc(sizeof(t_ph_data) * ft_atoi(argv[1]));
		data.thread = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
		data.f_mutex = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
		ft_init(argc, argv, &data, ph_data);
		ft_thread(ph_data, &data);
		//ft_print_philo_data(ph_data, &data);
		ft_clear(ph_data, &data);
		printf("%d\n", mail);
	}
	else
		return (arg_count_err());
	return (0);
}
