/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:39:52 by vcereced          #+#    #+#             */
/*   Updated: 2023/06/21 15:35:56 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h> 
# include <sys/stat.h>
# include <sys/types.h>

typedef struct timeval	t_timeval;

typedef struct s_philo
{
	int				argc;
	int				n;
	int				eaten;
	long long		start;
	long long		last;
	int				n_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_times_must_eat;
	int				arr_pids[200];
	pthread_t		thread;
	sem_t			*m_last;
	sem_t			*m_eaten;
	sem_t			*m_times_eat;
	sem_t			*sem_write;
	sem_t			*sem_finish;
}					t_philo;

//ERRORS
int			check_arg(int argc, char **argv);
int			msg_error(char *str);

//CREATE PROCESS
int			create_process(t_philo *philo, sem_t *sem_forks);

//forks
void		take_forks(t_philo *philo, t_timeval *t, sem_t *sem_forks);
void		leave_forks(sem_t *sem_forks);

//kill
void		kill_process(t_philo *philo);

//check game	
void		*check_game(void *ptr);
void		*check_ate_child(void *ptr);

//UTILS
int			ft_strlen(char *str);
int			ft_atoi(const char *str);
int			init_sems(t_philo *philo, sem_t **sem_forks);
int			unlink_sems(void);
#endif
