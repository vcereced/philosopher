/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 20:21:37 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/21 14:21:20 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*ft_new_node(int i, t_rules *rules)
{
	t_philo	*ptr;

	ptr = (t_philo *)malloc(sizeof(t_philo));
	if (!ptr)
		msg_error("error alocation memory\n");
	ptr -> n = i;
	ptr -> eaten = 0;
	ptr -> start = rules -> time;
	ptr -> last = rules -> time;
	ptr -> n_philosophers = rules -> n_philosophers;
	ptr -> time_to_die = rules -> time_to_die;
	ptr -> time_to_eat = rules -> time_to_eat;
	ptr -> time_to_sleep = rules -> time_to_sleep;
	if (rules -> argc == 6)
		ptr -> n_times_must_eat = rules -> n_times_must_eat;
	ptr -> rules = rules;
	ptr -> next = NULL;
	init_mutex(&ptr->fork);
	init_mutex(&ptr->m_last);
	init_mutex(&ptr->m_eaten);
	return (ptr);
}

static void	ft_add_back_node(t_philo *ptr, t_philo *new)
{
	while (ptr -> next)
		ptr = ptr -> next;
	ptr -> next = new;
}

static void	sit_philo_at_table(t_philo **philo, int i, t_rules *rules)
{
	if (i == 1)
		*philo = ft_new_node(i, rules);
	else
		ft_add_back_node(*philo, ft_new_node(i, rules));
}

static void	sit_last_philo_at_table(t_philo *philo)
{
	t_philo	*first;

	first = philo;
	while (philo -> next)
		philo = philo -> next;
	philo -> next = first;
}

void	set_table(t_philo **philo, t_rules *rules)
{
	int	i;

	i = 1;
	while (i <= rules->n_philosophers)
	{
		sit_philo_at_table(philo, i, rules);
		i++;
	}
	sit_last_philo_at_table(*philo);
}
