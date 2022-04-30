/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:24:24 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/04/30 13:17:39 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philosopher (void *phi)
{
	int left_fork;
	int right_fork;
	size_t time;
	size_t t;
	size_t start;
	
	t = get_time();
	start = get_time();
	t_phi *phi1 = (t_phi *)phi;
	t_data *data = phi1->s;
	while (1)
	{
		left_fork = phi1->id;
		right_fork = (phi1->id + 1) % (data->pno);
		lock_stick(data, left_fork, right_fork, start);
		pthread_mutex_lock(&data->task[0]);
		if (data->flag)
			check_meal(phi);
		pthread_mutex_unlock(&data->task[0]);
		check_death(phi1, get_time(), t, start);
		time = time_event(phi1, data->tte, t, start);
		t = get_time();
		unlock_stick(data, left_fork, right_fork, start);
		time = time_event(phi1, data->tts, t, start);
		pthread_mutex_lock(&data->task[0]);
		ft_printf("%d %d is thinking \n", (int)get_time() - start, phi1->id);
		pthread_mutex_unlock(&data->task[0]);
	}
	printf ("Philosopher %d is done eating.\n", phi1->id);
	return (NULL);
}