/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:33:37 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/21 17:32:13 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
/*
void	check_leaks(void)
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
static void	set_rules(t_rules *rules, int argc, char **argv)
{
	rules->argc = argc;
	rules->time = set_time_start();
	rules->n_philosophers = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules->n_times_must_eat = ft_atoi(argv[5]);
	init_mutex(&rules->m_write);
}

//	atexit(check_leaks);
int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_rules	rules;

	if (check_arg(argc, argv) == 1)
		return (0);
	set_rules(&rules, argc, argv);
	set_table(&philo, &rules);
	start_game(philo);
	check_game(philo);
	free_game(philo, argv);
	return (0);
}
