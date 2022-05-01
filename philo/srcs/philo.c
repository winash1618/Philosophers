/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:24:24 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/05/01 12:00:12 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(t_phi *phi, int flag)
{
	t_data	*data;

	data = phi->s;
	if (flag == 1)
	{
		data->death = 1;
	}
	else if (flag == 2)
	{
		data->death = 1;
	}
}

void	philoop(t_phi *phi1, t_data *data, size_t *d)
{
	while (1 && !data->death)
	{
		d[0] = phi1->id;
		d[1] = (phi1->id + 1) % (data->pno);
		lock_stick(data, d[0], d[1], d[4]);
		pthread_mutex_lock(&data->task[0]);
		if (data->flag)
			check_meal(phi1);
		pthread_mutex_unlock(&data->task[0]);
		check_death(phi1, get_time(), d[3], d[4]);
		d[2] = time_event(phi1, data->tte, d[3], d[4]);
		d[3] = get_time();
		pthread_mutex_lock(&data->task[1]);
		if (data->death)
		{
			pthread_mutex_unlock(&data->fork[d[0]]);
			pthread_mutex_unlock(&data->fork[d[1]]);
			pthread_mutex_unlock(&data->task[1]);
			break ;
		}
		pthread_mutex_unlock(&data->task[1]);
		unlock_stick(data, d[0], d[1], d[4]);
		d[2] = time_event(phi1, data->tts, d[3], d[4]);
		pthread_mutex_lock(&data->task[0]);
		if (!data->death)
			ft_printf("%d %d is thinking \n", (int)get_time() - d[4], phi1->id);
		pthread_mutex_unlock(&data->task[0]);
	}
}

void	*philosopher(void *phi)
{
	size_t	d[5];
	t_phi	*phi1;
	t_data	*data;

	d[3] = get_time();
	d[4] = d[3];
	phi1 = (t_phi *)phi;
	data = phi1->s;
	philoop(phi1, data, d);
	return (NULL);
}
