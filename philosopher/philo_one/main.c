/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 14:52:14 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/20 18:31:39 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int mail = 0;

void	ft_init(int argc, char **argv, t_data *data, t_philo *philo)
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
		philo[i].ph_number = i + 1;
		philo[i].tt_die = ft_atoi(argv[2]);
		philo[i].tt_eat = ft_atoi(argv[3]);
		philo[i].tt_sleep = ft_atoi(argv[4]);
		philo[i].data = data;
		pthread_mutex_init(&(data->f_mutex)[i], NULL);
		i++;
	}
}

void	ft_print_philo_data(t_philo *philo, t_data *data)
{
	int i;

	i = 0;
	printf("%d philosopher on table\n", data->n_philos);
	if (data->max_ph_eat != -1)
		printf("each philosopher should eat max %d times\n", data->max_ph_eat);
	printf("**************\n");
	while (i < data->n_philos)
	{
		printf("%d philo number %d \n", i, philo[i].ph_number);
		printf("----------------\n");
		printf("time_to_die : %d\n", philo[i].tt_die);
		printf("time_to_eat : %d\n", philo[i].tt_eat);
		printf("time_to_sleep : %d\n\n", philo[i].tt_sleep);
		i++;
	}
}

void	ft_clear(t_philo *philo, t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&(data->f_mutex)[i]);
		i++;
	}
	free(philo);
	free(data->thread);
}

void	*ft_routine(void *v_philo)
{
	t_data *data;
	t_philo *philo;
	
	philo = (t_philo *)v_philo;
	//printf(N);
	//mail++;
	data = philo->data;
	//printf("%d\n", philo->ph_number);
	while (1)
	{
		pthread_mutex_lock(&(data->f_mutex)[RIGHT]);
		printf("philo %d take right fork\n", philo->ph_number);
		pthread_mutex_lock(&(data->f_mutex)[LEFT]);
		printf("philo %d take left fork\n", philo->ph_number);
		
		printf("philo %d eating\n", philo->ph_number);
		sleep(2);
		pthread_mutex_unlock(&(data->f_mutex)[LEFT]);
		pthread_mutex_unlock(&(data->f_mutex)[RIGHT]);
		sleep(2);
	}
	return ((void*)0);
}

void	ft_thread(t_philo *philo, t_data *data)
{
	int i;

	i = 0;
	while (i < data->n_philos)
	{
		//data->ph_counter = i;
		pthread_create(&data->thread[i], NULL, &ft_routine, philo);
		//printf("thread %d created\n", i);
		philo++;
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
	t_philo		*philo;

	if (argc == 5 || argc == 6)
	{
		philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
		data.thread = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
		data.f_mutex = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
		ft_init(argc, argv, &data, philo);
		ft_thread(philo, &data);
		//ft_print_philo_data(philo, &data);
		ft_clear(philo, &data);
		printf("%d\n", mail);
	}
	else
		return (arg_count_err());
	return (0);
}
