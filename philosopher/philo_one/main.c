/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 14:52:14 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/18 19:51:34 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
	while (ph_data)
	{
		printf("ok\n");
		ph_data++;
	}
	
}

int main(int argc, char **argv)
{
	t_data		data;
	t_ph_data	*ph_data;

	if (argc == 5 || argc == 6)
	{
		ph_data = malloc(sizeof(t_ph_data) * ft_atoi(argv[1]));
		ft_init_philos(argc, argv, &data, ph_data);
		ft_print_philo_data(ph_data, &data);
	}
	else
		return (arg_count_err());
	return (0);
}
