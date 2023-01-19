/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:35:12 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/06/01 09:28:55 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	threading(t_phi *phi, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->pno)
	{
		pthread_create (&phi[i].phi_t, NULL, philosopher, (void *)&phi[i]);
		usleep(500);
	}
	i = -1;
	while (++i < data->pno)
		pthread_join (phi[i].phi_t, NULL);
	i = -1;
	while (++i < 5)
		pthread_mutex_destroy(&data->task[i]);
	i = -1;
	while (++i < data->pno)
		pthread_mutex_destroy(&data->fork[i]);
	free (data->fork);
	free (data->task);
	free (data);
	free (phi);
	return ;
}

void	init_philo(t_phi *phi, t_data *data, int t)
{
	int	i;

	i = -1;
	data->death = 0;
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
	threading(phi, data);
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
	data->flag_death = 0;
	if (ac == 6)
		t = ft_atop(av[5]);
	else
		t = 0;
	i = -1;
	data->task = malloc(sizeof(pthread_mutex_t) * 5);
	while (++i < 5)
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
		|| ft_atop(av[4]) < 60 || ft_atop(av[1]) < 1 )
		return ;
	else if (ft_atop(av[1]) == 1)
		printf("%d %d died \n", ft_atop(av[2]), 1);
	else if (ft_atop(av[ac - 1]) < 1 && ac == 6)
		return ;
	else
		init_data(ac, av);
}

int	main(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	if (ac > 6 || ac < 5)
	{
		printf("Error\n");
		printf("Please enter correct format\n");
	}
	else
	{
		while (++i < ac)
		{
			j = -1;
			while (av[i][++j])
				if (!ft_isdigit(av[i][j]) && av[i][0] != '+')
					return (0);
		}
		init_check(ac, av);
	}
	return (0);
}
