/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:50:58 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/21 17:32:20 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	leave_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->fork));
	pthread_mutex_unlock(&(philo->next->fork));
}

/**
 * @brief trying lock a fork, then lock writing, print the msg, unlock writing. 
 * Do again the same for a second fork.
 */
void	take_forks(t_philo *philo, t_timeval *t)
{
	pthread_mutex_lock(&(philo -> fork));
	pthread_mutex_lock(&philo->rules->m_write);
	gettimeofday(t, NULL);
	printf("%lld p%d has taken a fork\n", ((t->tv_sec) * 1000 + (t->tv_usec) \
	/ 1000) - philo -> start, philo->n);
	pthread_mutex_unlock(&philo->rules->m_write);
	pthread_mutex_lock(&(philo -> next -> fork));
	pthread_mutex_lock(&philo->rules->m_write);
	gettimeofday(t, NULL);
	printf("%lld p%d has taken a fork2\n", ((t->tv_sec) * 1000 + (t->tv_usec) \
	/ 1000) - philo -> start, philo->n);
	pthread_mutex_unlock(&philo->rules->m_write);
}
