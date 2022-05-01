/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:26:24 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/05/01 12:47:42 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdarg.h>

typedef struct common_data
{
	int				pno;
	int				flag;
	int				death;
	int				flag_death;
	size_t			ttd;
	size_t			tte;
	size_t			tts;
	size_t			tt;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*task;
}	t_data;

typedef struct philo
{
	int			id;
	int			nte;
	pthread_t	phi_t;
	t_data		*s;
}	t_phi;

void	lock_stick(t_data *data, int left_fork, int right_fork, size_t start);
void	unlock_stick(t_data *data, int left_fork, int right_fork, size_t start);
size_t	get_time(void);
void	check_death(t_phi *phi, size_t ta, size_t tb, size_t ts);
size_t	time_event(t_phi *phi, size_t ptime, size_t t, size_t ts);
void	*philosopher(void *phi);
int		ft_atop(const char *str);
void	check_meal(t_phi *phi);
void	ft_error(t_phi *phi, int flag);
int		ft_printf(const char *arg, ...);
int		ft_charcheck(char c, va_list ap);
int		ft_putchar(int c);
int		ft_putstr(char *str);
int		ft_putint(int num);
void	printer(t_data *data, int time, int id, int flag);

#endif
