/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:33:37 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/21 17:45:11 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*void	check_leaks(void)
{
	system("leaks philo");
}*/
/**
 * @brief Set the time start object
 */
static long long	set_time_start(void)
{
	t_timeval	start;

	gettimeofday(&start, NULL);
	return ((start.tv_sec) * 1000 + (start.tv_usec) / 1000);
}

/**
 * @brief Set the rules object
 */
static void	set_rules(t_philo *philo, int argc, char **argv)
{
	philo -> n = 0;
	philo -> eaten = 0;
	philo -> argc = argc;
	philo -> start = set_time_start();
	philo -> last = philo -> start;
	philo -> n_philosophers = ft_atoi(argv[1]);
	philo -> time_to_die = ft_atoi(argv[2]);
	philo -> time_to_eat = ft_atoi(argv[3]);
	philo -> time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->n_times_must_eat = ft_atoi(argv[5]);
	else
		philo->n_times_must_eat = 0;
}

/**
 * @brief unlink before and after the program run because the sems stay 
 * in the system so must to be removed.
*/
int	unlink_sems(void)
{
	sem_unlink("/semaphore_write");
	sem_unlink("/semaphore_forks");
	sem_unlink("/semaphore_finish");
	sem_unlink("/semaphore_last");
	sem_unlink("/semaphore_eaten");
	sem_unlink("/semaphore_m_times_eaten");
	return (errno);
}

int	main(int argc, char **argv)
{
	t_philo		philo;
	sem_t		*sem_forks;
	pthread_t	thread;

	unlink_sems();
	if (check_arg(argc, argv) == 1)
		return (0);
	set_rules(&philo, argc, argv);
	if (init_sems(&philo, &sem_forks) == 1)
		return (unlink_sems());
	if (create_process(&philo, sem_forks) != 0)
		return (errno);
	if (argc == 6)
	{
		pthread_create(&thread, NULL, check_ate_child, &philo);
		pthread_detach(thread);
	}
	sem_wait(philo.sem_finish);
	kill_process(&philo);
	unlink_sems();
	return (0);
}
