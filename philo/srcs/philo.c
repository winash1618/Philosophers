/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:24:24 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/04/30 06:09:22 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philosopher (void *phi)
{
	int left_fork;
	int right_fork;
	size_t time;
	size_t t;
	t= get_time();
	size_t start;
	start = get_time();
	t_phi *phi1 = (t_phi *)phi;
	t_data *data = phi1->s;
	while (1)
	{
		left_fork = phi1->id;
		right_fork = (phi1->id + 1) % (data->pno);
		lock_stick(data, left_fork, right_fork, start);
		check_death(data, get_time(), t);
		time = time_event(data, data->tte, t);
		t = get_time();
		pthread_mutex_lock(&data->task[3]);
		data->tt += time;
		pthread_mutex_unlock(&data->task[3]);
		unlock_stick(data, left_fork, right_fork, start);
		time = time_event(data, data->tts, t);
		pthread_mutex_lock(&data->task[3]);
		data->tt += time;
		ft_printf("%d %d is thinking \n", (int)get_time() - start, phi1->id);
		pthread_mutex_unlock(&data->task[3]);
	}
	printf ("Philosopher %d is done eating.\n", phi1->id);
	return (NULL);
}

int main()
{
	t_phi *phi;

	phi = malloc(sizeof(t_phi) * 5);
	t_data *data;
	data  = malloc(sizeof(t_data));
	data->pno = 5;
	data->ttd = 800;
	data->tte = 200;
	data->tts = 200;
	data->tt = 0;
	int i = 0;
	data->task = malloc(sizeof(pthread_mutex_t) * 10);
	while (i < 10)
	{
		pthread_mutex_init(&data->task[i], NULL);
		i++;
	}
	data->fork = malloc(sizeof(pthread_mutex_t) * 5);
	i = 0;
	while (i < 5)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		phi[i].id = i;
		phi[i].s = data; 
		i++;
	}
	i = 0;
	while (i < 5)
	{
		printf("%d %p %p\n", phi[i].id, &phi[i].s->fork[i], &phi[i].s->task[i]);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		pthread_create (&phi[i].phi_t, NULL, philosopher, (void *)&phi[i]);
		usleep(300);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		pthread_join (phi[i].phi_t, NULL);
	}
}