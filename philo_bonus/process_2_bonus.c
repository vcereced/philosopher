/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:50:58 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/21 15:33:57 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
/**
 * @brief post the forks
 */
void	leave_forks(sem_t *sem_forks)
{
	sem_post(sem_forks);
	sem_post(sem_forks);
}

/**
 * @brief trying to wait the semaphore of a fork, then wait the sem of 
 * writing, print the msg, post the sem of writing. Do again the same for 
 * a second fork.
 */
void	take_forks(t_philo *philo, t_timeval *t, sem_t *sem_forks)
{
	sem_wait(sem_forks);
	sem_wait(philo -> sem_write);
	gettimeofday(t, NULL);
	printf("%lld p%d has taken a fork\n", ((t->tv_sec) * 1000 + (t->tv_usec) \
	/ 1000) - philo -> start, philo->n);
	sem_post(philo -> sem_write);
	sem_wait(sem_forks);
	sem_wait(philo -> sem_write);
	gettimeofday(t, NULL);
	printf("%lld p%d has taken a fork2\n", ((t->tv_sec) * 1000 + (t->tv_usec) \
	/ 1000) - philo -> start, philo->n);
	sem_post(philo -> sem_write);
}
