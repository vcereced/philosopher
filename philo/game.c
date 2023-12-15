/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:11:04 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/21 17:11:50 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief First trying lock 2 forks, then lock writing, get the time,
 * lock value of the last meal. then print the msg, unlock the value of the 
 * last meal, unlock write. Do usleep of time_to_eat. Do the same to the value
 * of philo->eaten.
 */
void	eat(t_philo *philo, t_timeval *t)
{
	take_forks(philo, t);
	pthread_mutex_lock(&philo->rules->m_write);
	gettimeofday(t, NULL);
	pthread_mutex_lock(&philo->m_last);
	philo->last = ((t->tv_sec) * 1000 + (t->tv_usec) / 1000);
	printf("%lld p%d is eating\n", philo -> last - philo-> start, philo -> n);
	pthread_mutex_unlock(&philo->m_last);
	pthread_mutex_unlock(&philo->rules->m_write);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_lock(&philo->m_eaten);
	usleep(100);
	(philo->eaten)++;
	pthread_mutex_unlock(&philo->m_eaten);
	leave_forks(philo);
}

/**
 * @brief lock of writing, get the time, print msg 
 * and unlock of writing.
 */
void	think(t_philo *philo, t_timeval *tv)
{
	pthread_mutex_lock(&philo->rules->m_write);
	gettimeofday(tv, NULL);
	printf("%lld p%d is thinking\n", ((tv->tv_sec) * 1000 + (tv->tv_usec) / \
	1000) - philo -> start, philo -> n);
	pthread_mutex_unlock(&philo->rules->m_write);
}

/**
 * @brief lock of writing, get the time, print msg, usleep
 * time_to_sleep and unlock of writing.
 */
void	slep(t_philo *philo, t_timeval *t)
{
	pthread_mutex_lock(&philo->rules->m_write);
	gettimeofday(t, NULL);
	printf("%lld p%d is sleeping\n", ((t->tv_sec) * 1000 + (t->tv_usec) / \
	1000) - philo -> start, philo -> n);
	pthread_mutex_unlock(&philo->rules->m_write);
	usleep(philo->time_to_sleep * 1000);
}

/**
 * @brief Function called after pthread created. Even philos 
 * starting eating, odd sleeping. 
 */
void	*philosopher(void *ptr)
{
	t_timeval	t;
	t_philo		*philo;

	philo = (t_philo *)ptr;
	if (philo->n % 2 == 0)
	{
		while (42)
		{
			eat(philo, &t);
			slep(philo, &t);
			think(philo, &t);
		}
	}
	while (42)
	{
		slep(philo, &t);
		think(philo, &t);
		eat(philo, &t);
	}
	return (ptr);
}

void	start_game(t_philo *philo)
{
	int	i;

	i = 1;
	while (i <= philo->rules->n_philosophers)
	{
		pthread_create(&(philo->thread), NULL, philosopher, philo);
		pthread_detach(philo->thread);
		philo = philo -> next;
		i++;
	}
}
