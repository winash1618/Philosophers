/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:26:44 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/04/30 11:45:25 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void lock_stick(t_data *data, int left_fork, int right_fork, size_t start)
{
	if (left_fork % 2 != 0)
	{
		pthread_mutex_lock(&data->fork[left_fork]);
		pthread_mutex_lock(&data->fork[right_fork]);
	}
	else
	{
		ft_printf("hi");
		pthread_mutex_lock(&data->fork[right_fork]);
		pthread_mutex_lock(&data->fork[left_fork]);
	}
	pthread_mutex_lock(&data->task[3]);
	ft_printf("%d %d has taken a fork\n", (int)get_time() - start, left_fork);
	ft_printf("%d %d has taken a fork\n", (int)get_time() - start, left_fork);
	ft_printf("%d %d is eating\n", (int)get_time() - start, left_fork);
	pthread_mutex_unlock(&data->task[3]);
}

void unlock_stick(t_data *data, int left_fork, int right_fork, size_t start)
{
	
	pthread_mutex_unlock(&data->fork[left_fork]);
	pthread_mutex_unlock(&data->fork[right_fork]);
	pthread_mutex_lock(&data->task[3]);
	ft_printf("%d %d is sleeping \n", (int)get_time() - start, left_fork);
	pthread_mutex_unlock(&data->task[3]);
	
}