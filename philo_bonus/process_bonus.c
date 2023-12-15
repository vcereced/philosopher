/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:20:20 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/21 17:32:03 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
/**
 * @brief First trying to wait 2 semaphores forks, then wait the semaphore of 
 * writing, get the time, wait the semaphore of value of the last meal. then 
 * print the msg, post the semaphore of the value of the last meal, post 
 * the semaphore of write. Do usleep of time_to_eat. Do the same to the value
 * of philo->eaten and if eaten the number of times post philo->m_times_eat.
 */
void	eat(t_philo *philo, t_timeval *t, sem_t *sem_forks)
{
	take_forks(philo, t, sem_forks);
	sem_wait(philo -> sem_write);
	gettimeofday(t, NULL);
	sem_wait(philo -> m_last);
	philo->last = ((t->tv_sec) * 1000 + (t->tv_usec) / 1000);
	sem_post(philo->m_last);
	printf("%lld p%d is eating\n", philo -> last - philo-> start, philo -> n);
	sem_post(philo -> sem_write);
	usleep(philo -> time_to_eat * 1000);
	sem_wait(philo -> m_eaten);
	(philo->eaten)++;
	if (philo -> eaten == philo -> n_times_must_eat)
	{
		sem_post(philo -> m_times_eat);
	}
	sem_post(philo -> m_eaten);
	leave_forks(sem_forks);
}

/**
 * @brief wait the semaphore of writing, get the time, print msg, usleep
 * time_to_sleep and post the semaphore of writing.
 */
void	slep(t_philo *philo, t_timeval *t)
{
	sem_wait(philo -> sem_write);
	gettimeofday(t, NULL);
	printf("%lld p%d is sleeping\n", ((t->tv_sec) * 1000 + (t->tv_usec) / \
	1000) - philo -> start, philo -> n);
	sem_post(philo -> sem_write);
	usleep(philo -> time_to_sleep * 1000);
}

/**
 * @brief wait the semaphore of writing, get the time, print msg 
 * and post the semaphore of writing.
 */
void	think(t_philo *philo, t_timeval *t)
{
	sem_wait(philo -> sem_write);
	gettimeofday(t, NULL);
	printf("%lld p%d is thinking\n", ((t->tv_sec) * 1000 + (t->tv_usec) / \
	1000) - philo -> start, philo -> n);
	sem_post(philo -> sem_write);
}

/**
 * @brief Function called after fork. It create a thread for check the life
 * of itself. Even philos starting eating, odd sleeping. 
 */
void	philosopher(t_philo *philo, sem_t *sem_forks)
{
	t_timeval	t;

	pthread_create(&philo->thread, NULL, check_game, philo);
	pthread_detach(philo->thread);
	if (philo->n % 2 == 0)
	{
		while (42)
		{
			eat(philo, &t, sem_forks);
			slep(philo, &t);
			think(philo, &t);
		}
	}
	while (42)
	{
		slep(philo, &t);
		think(philo, &t);
		eat(philo, &t, sem_forks);
	}
}

/**
 * @brief Create a process object of every philosopher. Also store every
 * pid created for to be killed later.
 * @return int 0 if OK. errno if error.
 */
int	create_process(t_philo *philo, sem_t *sem_forks)
{
	int	n;
	int	pid;

	n = 1;
	while (n <= philo->n_philosophers)
	{
		philo -> n = n;
		pid = fork();
		if (pid == -1)
			return (unlink_sems());
		if (pid == 0)
			philosopher(philo, sem_forks);
		philo -> arr_pids[n - 1] = pid;
		n++;
	}
	philo -> arr_pids[n - 1] = 0;
	return (0);
}
