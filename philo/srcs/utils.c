/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:26:17 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/04/30 10:30:30 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, 0);
	return((tv.tv_sec*1000 + tv.tv_usec/1000));
}

void check_death(t_data *data, size_t time_after, size_t time_before)
{
	if (time_after - time_before >= data->ttd)
		exit(1);
}

size_t time_event(t_data *data, size_t ptime, size_t t)
{
	size_t	time;

	time = get_time();
	while (1)
	{
		if (check_death(data, get_time(), t), (get_time() - time) >= ptime)
			break;
		usleep(100);
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
