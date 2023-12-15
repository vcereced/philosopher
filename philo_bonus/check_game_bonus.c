/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_game_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:55:31 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/21 17:30:02 by vcereced         ###   ########.fr       */
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

int	check_life(t_philo *philo, int *limit)
{
	t_timeval	t;
	int			i;
	long long	now;
	long long	last;

	i = 0;
	gettimeofday(&t, NULL);
	now = (t.tv_sec) * 1000 + (t.tv_usec) / 1000;
	sem_wait(philo->m_last);
	last = philo->last;
	sem_post(philo->m_last);
	if ((now - last) > *limit)
	{
		sem_wait(philo->sem_write);
		msg(now - philo->start, philo -> n, philo->start, now - last);
		sem_post(philo->sem_finish);
		return (1);
	}
	return (0);
}

void	*check_game(void *ptr)
{
	int			limit;
	t_philo		*philo;

	philo = (t_philo *)ptr;
	limit = philo->time_to_die;
	while (42)
	{
		if (check_life(philo, &limit) == 1)
			return (0);
		usleep(1000);
	}
}

void	kill_process(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo->arr_pids[i] != 0)
	{
		kill(philo->arr_pids[i], 9);
		i++;
	}
}
