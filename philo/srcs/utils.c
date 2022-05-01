/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:26:17 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/05/01 12:49:00 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void printer(t_data *data, int time, int id, int flag)
{
	
	if (flag == 1 && !data->flag_death)
	{
		data->flag_death = 1;
		ft_printf("%d %d died\n", time, id);
	}
	else if (flag == 2 && !data->flag_death)
	{
		ft_printf("%d %d has taken a fork\n", time, id);
		ft_printf("%d %d has taken a fork\n", time, id);
		ft_printf("%d %d is eating\n", time, id);
	}
	else if (flag == 3 && !data->flag_death)
	{
		 ft_printf("%d %d is thinking \n", time, id);
	}
	else if (flag == 4 && !data->flag_death)
	{
		ft_printf("%d %d is sleeping \n", time, id);
	}
}
size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

void	check_death(t_phi *phi, size_t ta, size_t tb, size_t ts)
{
	t_data	*data;

	data = phi->s;
	if (ta - tb >= data->ttd && !data->death)
	{
		pthread_mutex_lock(&data->task[0]);
		printer(data, (int)get_time() - ts, phi->id, 1);
		// ft_printf("%d %d died\n", (int)get_time() - ts, phi->id);
		pthread_mutex_unlock(&data->task[0]);
		ft_error(phi, 2);
	}
}

size_t	time_event(t_phi *phi, size_t ptime, size_t t, size_t ts)
{
	size_t	time;

	time = get_time();
	while (1)
	{
		usleep(100);
		if (check_death(phi, get_time(), t, ts), (get_time() - time) >= ptime)
			break ;
	}
	return (get_time() - time);
}

int	ft_atop(const char *str)
{
	int				count;
	unsigned int	sum;

	count = 1;
	sum = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\f'
		|| *str == '\r' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			count = -count;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		sum = sum * 10 + (*str - '0');
		str++;
		if (sum > 2147483647)
			exit (1);
	}
	return (sum * count);
}
