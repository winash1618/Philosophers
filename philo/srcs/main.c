/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:35:12 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/04/30 14:41:13 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_phi *phi, t_data *data, int t)
{
	int	i;

	i = -1;
	while (++i < data->pno)
	{
		phi[i].id = i;
		phi[i].s = data;
		if (t)
		{
			phi[i].nte = t;
			data->flag = 1;
		}
		else
			data->flag = 0;
	}
	i = -1;
	while (++i < data->pno)
	{
		pthread_create (&phi[i].phi_t, NULL, philosopher, (void *)&phi[i]);
		usleep(300);
	}
	i = -1;
	while (++i < data->pno)
		pthread_join (phi[i].phi_t, NULL);
}

void	init_data(int ac, char **av)
{
	t_phi	*phi;
	t_data	*data;
	int		t;
	int		i;

	phi = malloc(sizeof(t_phi) * ft_atop(av[1]));
	data = malloc(sizeof(t_data));
	data->pno = ft_atop(av[1]);
	data->ttd = ft_atop(av[2]);
	data->tte = ft_atop(av[3]);
	data->tts = ft_atop(av[4]);
	if (ac == 6)
		t = ft_atop(av[5]);
	else
		t = 0;
	i = -1;
	data->task = malloc(sizeof(pthread_mutex_t) * data->pno);
	while (++i < data->pno)
		pthread_mutex_init(&data->task[i], NULL);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->pno);
	i = -1;
	while (++i < data->pno)
		pthread_mutex_init(&data->fork[i], NULL);
	init_philo(phi, data, t);
}

void	init_check(int ac, char **av)
{
	if (ft_atop(av[1]) > 200 || ft_atop(av[2]) < 60 || ft_atop(av[3]) < 60
		|| ft_atop(av[4]) < 60 || ft_atop(av[1]) < 2)
		exit(1);
	else
		init_data(ac, av);
}

void	check_philo(int ac, char **av)
{
	if (ac > 6 || ac < 5)
	{
		printf("Error\n");
		printf("Please enter correct format\n");
	}
	else
		init_check(ac, av);
}

int	main(int ac, char **av)
{
	check_philo(ac, av);
	return (0);
}
