/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:26:24 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/04/30 10:24:27 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include "../libft/ft_printf/includes/ft_printf.h"

typedef struct common_data
{
	int pno;
	int nte;
	size_t ttd;
	size_t tte;
	size_t tts;
	size_t tt;
	int e_max;
	pthread_mutex_t *fork;
	pthread_mutex_t *task;
}	t_data;

typedef struct philo
{
	int id;
	int nte;
	pthread_t phi_t;
	t_data *s;
}	t_phi;

void lock_stick(t_data *data, int left_fork, int right_fork, size_t start);
void unlock_stick(t_data *data, int left_fork, int right_fork, size_t start);
size_t get_time(void);
void check_death(t_data *data, size_t time_after, size_t time_before);
size_t time_event(t_data *data, size_t ptime, size_t t);
void *philosopher (void *phi);
int	ft_atop(const char *str);

#endif
