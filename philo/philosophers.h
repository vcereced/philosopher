/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:39:52 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/21 14:20:57 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct timeval	t_timeval;

typedef struct s_rules
{
	int				argc;
	long long		time;
	int				n_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_times_must_eat;
	pthread_mutex_t	m_write;
}					t_rules;

typedef struct s_philo
{
	int				n;
	int				eaten;
	long long		start;
	long long		last;
	int				n_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_times_must_eat;
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	m_last;
	pthread_mutex_t	m_eaten;
	t_rules			*rules;
	struct s_philo	*next;
}					t_philo;

//ERRORS
int			check_arg(int argc, char **argv);
int			msg_error(char *str);

//SET PHILOSOPHERS
void		set_table(t_philo **philo, t_rules *rules);

//START GAME
void		start_game(t_philo *philo);
void		leave_forks(t_philo *philo);
void		take_forks(t_philo *philo, t_timeval *t);

//CHECK LIFE& N_TIMES EATEN
void		check_game(t_philo *philo);

//FREE NODES OF PHILOSOPHERS
void		free_game(t_philo *philo, char **argv);

//UTILS
void		init_mutex(pthread_mutex_t *mutex);
void		free_game(t_philo *philo, char **argv);
int			ft_atoi(const char *str);
int			ft_strlen(char *str);

#endif
