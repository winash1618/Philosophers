/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:26:44 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/05/01 11:58:43 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_stick(t_data *data, int left_fork, int right_fork, size_t start)
{
	if (!data->death)
	{
		if (left_fork % 2 != 0)
		{
			pthread_mutex_lock(&data->fork[left_fork]);
			pthread_mutex_lock(&data->fork[right_fork]);
		}
		else
		{
			pthread_mutex_lock(&data->fork[right_fork]);
			pthread_mutex_lock(&data->fork[left_fork]);
		}
		pthread_mutex_lock(&data->task[0]);
		ft_printf("%d %d has taken a fork\n", (int)get_time() - start, left_fork);
		ft_printf("%d %d has taken a fork\n", (int)get_time() - start, left_fork);
		ft_printf("%d %d is eating\n", (int)get_time() - start, left_fork);
		pthread_mutex_unlock(&data->task[0]);
	}
}

void	unlock_stick(t_data *data, int left_fork, int right_fork, size_t start)
{
	if (!data->death)
	{
		pthread_mutex_unlock(&data->fork[left_fork]);
		pthread_mutex_unlock(&data->fork[right_fork]);
		pthread_mutex_lock(&data->task[0]);
		ft_printf("%d %d is sleeping \n", (int)get_time() - start, left_fork);
		pthread_mutex_unlock(&data->task[0]);
	}
}

void	check_meal(t_phi *phi)
{
	if (phi->nte)
	{
		phi->nte -= 1;
	}
	else
		ft_error(phi, 1);
}
