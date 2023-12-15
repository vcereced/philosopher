/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:28:41 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/21 17:31:25 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	minus;
	int	aux;

	i = 0;
	minus = 1;
	aux = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		aux = (str[i] - '0') + (aux * 10);
		i++;
	}
	aux *= minus;
	return (aux);
}

/**
 * @brief that funcion tries to wait the semaphore of 
 * times of each philo eaten. if it can be waited means a philo
 * is full eaten. its function have a counter. if send waits equal 
 * to the counter means all philo eaten so post the sem to finish
 * the program.
 */
void	*check_ate_child(void *ptr)
{
	t_philo		*philo;
	int			n;
	int			i;

	philo = (t_philo *)ptr;
	n = philo->n_philosophers;
	i = 0;
	while (i < n)
	{
		sem_wait(philo->m_times_eat);
		i++;
		usleep(100);
	}
	sem_wait(philo->sem_write);
	write(1, "ALL EATED\n", 11);
	sem_post(philo->sem_finish);
	return (0);
}

/**
 * @brief Create the semaphores with full permisions, for avoid date races,
 * sem_m_times_eat is full waited. any full eaten philo will post and a 
 * funcion in main thread of parent proccess will detect that post. 
 * @return int int 0 if O, 1 if any error occur.
 */
int	init_sems2(t_philo *philo)
{
	int	i;

	i = 0;
	philo -> m_eaten = sem_open("/semaphore_eaten", O_CREAT, 0666, 1);
	if (philo -> m_eaten == SEM_FAILED)
		return (msg_error("sem_open"));
	if (philo->argc == 6)
	{
		philo -> m_times_eat = sem_open("/semaphore_m_times_eaten", O_CREAT, \
		0666, philo->n_philosophers);
		if (philo->m_eaten == SEM_FAILED)
			return (msg_error("sem_open"));
		while (i != philo->n_philosophers)
		{
			sem_wait(philo->m_times_eat);
			i++;
		}
	}
	return (0);
}

/**
 * @brief Create the semaphores with full permisions, also block the semaphore
 *  *sem_finish. it will used to start the main thread to finish the program
 * @return int 0 if O, 1 if any error occur.
 */
int	init_sems(t_philo *philo, sem_t **sem_forks)
{
	philo->sem_write = sem_open("/semaphore_write", O_CREAT, 0666, 1);
	if (philo -> sem_write == SEM_FAILED)
		return (msg_error("sem_open"));
	*sem_forks = sem_open("/semaphore_forks", O_CREAT, \
	0666, philo -> n_philosophers);
	if (*sem_forks == SEM_FAILED)
		return (msg_error("sem_open"));
	philo->sem_finish = sem_open("/semaphore_finish", O_CREAT, 0666, 1);
	if (philo -> sem_finish == SEM_FAILED)
		return (msg_error("sem_open"));
	sem_wait(philo->sem_finish);
	if (init_sems2(philo) == 1)
		return (1);
	return (0);
}
