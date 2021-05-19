/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 14:52:14 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/18 22:57:31 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

pthread_mutex_t mutex;
int mail = 0;

void	ft_init_philos(int argc, char **argv, t_data *data, t_ph_data *ph_data)
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

void	ft_clear(t_ph_data *ph_data, pthread_t *thread)
{
	free(ph_data);
	free(thread);
}

void	*ft_routine()
{
	int j;
	j = 0;
	while (j < 10000000)
	{
		pthread_mutex_lock(&mutex);
		mail++;
		pthread_mutex_unlock(&mutex);
		j++;
	}
}

void	ft_thread(pthread_t *thread, t_data *data)
{
	int i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_create(&thread[i], NULL, &ft_routine, NULL);
		printf("thread %d created\n", i);
		i++;
	}
	i = 0;
	while (i < data->n_philos)
	{
		pthread_join(thread[i], NULL);
		printf("thread %d finish his job\n", i);		
		i++;
	}
	
	
}

int main(int argc, char **argv)
{
	t_data		data;
	t_ph_data	*ph_data;
	pthread_t	*thread;

	if (argc == 5 || argc == 6)
	{
		pthread_mutex_init(&mutex, NULL);
		ph_data = malloc(sizeof(t_ph_data) * ft_atoi(argv[1]));
		thread = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
		ft_init_philos(argc, argv, &data, ph_data);
		ft_thread(thread, &data);
		//ft_print_philo_data(ph_data, &data);
		ft_clear(ph_data, thread);
		pthread_mutex_destroy(&mutex);
		printf("%d\n", mail);
	}
	else
		return (arg_count_err());
	return (0);
}
