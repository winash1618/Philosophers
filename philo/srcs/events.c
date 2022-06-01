/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:26:44 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/06/01 06:58:07 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_stick(t_data *data, int left_fork, int right_fork, size_t start)
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
	printer(data, get_time() - start, left_fork, 2);
	pthread_mutex_unlock(&data->task[0]);
}

void	unlock_stick(t_data *data, int left_fork, int right_fork, size_t start)
{
	pthread_mutex_unlock(&data->fork[left_fork]);
	pthread_mutex_unlock(&data->fork[right_fork]);
	pthread_mutex_lock(&data->task[0]);
	printer(data, get_time() - start, left_fork, 4);
	pthread_mutex_unlock(&data->task[0]);
}

void	check_meal(t_phi *phi)
{
	pthread_mutex_lock(&phi->s->task[2]);
	if (phi->nte)
		phi->nte -= 1;
	else
		ft_error(phi, 1);
	pthread_mutex_unlock(&phi->s->task[2]);
}
