/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:38:29 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/17 18:40:28 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_mutex(pthread_mutex_t *mutex)
{
	int	status;

	status = pthread_mutex_init(mutex, NULL);
	if (status)
		msg_error("error init mutex");
}

void	free_game(t_philo *philo, char **argv)
{
	t_philo	*ptr;
	int		n_philo;
	int		i;

	ptr = philo;
	n_philo = ft_atoi(argv[1]);
	i = 0;
	while (i < n_philo)
	{
		ptr = philo -> next;
		free(philo);
		philo = ptr;
		i++;
	}
}

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
