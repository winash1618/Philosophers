/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:24:24 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/05/01 09:34:02 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(t_phi *phi, int flag)
{
	t_data	*data;
	// int i;

	// i = -1;
	data = phi->s;
	if (flag == 1)
	{
		// printf("Meals Finished \n");
		data->death = 1;
		// i = -1;
		// while (++i < data->pno)
		// {
		// 	pthread_mutex_unlock(&data->fork[i]);
		// 	pthread_join (phi[i].phi_t, NULL);
		// 	pthread_mutex_unlock(&data->task[i]);
		// }
		// i = -1;
		// while (++i < data->pno)
		// {
		// 	pthread_detach (phi[i + 8].phi_t);
		// 	pthread_mutex_destroy(&data->fork[i]);
		// 	pthread_mutex_destroy(&data->task[i]);
		// }
		// free (data->task);
		// free (data->fork);
		// i = -1;
		// while (++i < data->pno)
		// {
		// 	free ((pthread_t *)phi[i].phi_t);
		// }
		// free (phi);
		// exit (1);
		// free (data->fork);
		// free (data->task);
		// free (data);
		// free (phi);
		// exit(1);
	}
	else if (flag == 2)
	{
		// printf("Simulation Ends \n");
		data->death = 1;
		// free (phi);
		// exit (1);
	}
}

void	philoop(t_phi *phi1, t_data *data, size_t *d)
{
	while (1)
	{
		d[0] = phi1->id;
		d[1] = (phi1->id + 1) % (data->pno);
		lock_stick(data, d[0], d[1], d[4]);
		pthread_mutex_lock(&data->task[0]);
		if (data->flag)
			check_meal(phi1);
		pthread_mutex_unlock(&data->task[0]);
		// if (data->death)
		// {
		// 	pthread_join (phi1[phi1->id].phi_t, NULL);	
		// 	if(!pthread_detach (phi1[phi1->id].phi_t))
		// 		printf("Error in detach\n");
		// }
		check_death(phi1, get_time(), d[3], d[4]);
		d[2] = time_event(phi1, data->tte, d[3], d[4]);
		d[3] = get_time();
		unlock_stick(data, d[0], d[1], d[4]);
		pthread_mutex_lock(&data->task[1]);
		if (data->death)
		{
			pthread_mutex_unlock(&data->task[1]);
			break;
			// pthread_join (phi1[phi1->id].phi_t, NULL);	
			// if(!pthread_detach (phi1[phi1->id].phi_t))
			// 	printf("Error in detach\n");
		}
		pthread_mutex_unlock(&data->task[1]);
		d[2] = time_event(phi1, data->tts, d[3], d[4]);
		pthread_mutex_lock(&data->task[0]);
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
	printf("Philosopher %d is done eating.\n", phi1->id);
	// int i;
	// i = -1;
	// while (++i < data->pno)
	// 	pthread_join (phi1[i].phi_t, NULL);
	// i = -1;
	// while (++i < data->pno)
	// {
	// 	if(pthread_detach (phi1[i].phi_t))
	// 		printf("Error in detach\n");
	// }
	// i = -1;
	// while (++i < data->pno)
	// {
	// 	free(phi1[i].phi_t);
	// }
	// free (data->fork);
	// free (data->task);
	// free (data);
	// free (phi);
	// exit(1);
	return (NULL);
}
