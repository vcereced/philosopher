/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:55:31 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/21 16:52:29 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	msg(long long now, int n, long long start, long long last_meal)
{
	t_timeval	t;

	gettimeofday(&t, NULL);
	usleep(5000);
	printf("%lld p%d has DIED \t\t*t.msg %lld *t.from last meal %lld\n", now, \
	n, (t.tv_sec) * 1000 + (t.tv_usec) / 1000 - start, last_meal);
}

int	check_life(t_philo *philo, int *limit, int *n_philo, t_timeval *t)
{
	int			i;
	long long	now;
	long long	last;

	i = 0;
	while (i < *n_philo)
	{
		gettimeofday(t, NULL);
		now = (t->tv_sec) * 1000 + (t->tv_usec) / 1000;
		pthread_mutex_lock(&philo->m_last);
		last = philo->last;
		pthread_mutex_unlock(&philo->m_last);
		if ((now - last) > *limit)
		{
			pthread_mutex_lock(&philo->rules->m_write);
			msg(now - philo->start, philo -> n, philo->start, now - last);
			return (1);
		}
		i++;
		philo = philo -> next;
	}
	return (0);
}

int	check_ate(t_philo *philo, int *n_philo, int *times_eaten)
{
	int	i;
	int	cont;

	i = 0;
	cont = 0;
	while (i < *n_philo)
	{
		pthread_mutex_lock(&philo->m_eaten);
		if (philo->eaten >= *times_eaten)
			cont++;
		pthread_mutex_unlock(&philo->m_eaten);
		philo = philo->next;
		i++;
	}
	if (cont >= *n_philo)
	{
		pthread_mutex_lock(&philo->rules->m_write);
		usleep(5000);
		write(1, "ALL EATEN!\n", 11);
		return (1);
	}
	return (0);
}

void	check_game(t_philo *philo)
{
	t_timeval	t;
	int			limit;
	int			n_philo;
	int			n_ate;

	n_philo = philo->rules->n_philosophers;
	limit = philo->rules->time_to_die;
	if (philo->rules->argc == 6)
		n_ate = philo->rules->n_times_must_eat;
	while (42)
	{
		if (check_life(philo, &limit, &n_philo, &t) == 1)
			return ;
		if (philo->rules->argc == 6 && check_ate(philo, &n_philo, &n_ate) == 1)
			return ;
		usleep(10);
	}
}
