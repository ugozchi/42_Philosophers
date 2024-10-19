/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:52:05 by uzanchi           #+#    #+#             */
/*   Updated: 2024/10/19 19:16:55 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/*libraries*/
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <time.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

/*MESSAGES*/
/*Errors*/
# define WRG_ARG_NR "The program expects 4 or 5 arguments: \
number_of_philosophers, time_to_die, time_to_eat, time_to_sleep and \
number_of_times_each_philosopher_must_eat (optional)\n"
# define INVALID_ARG "%s is an invalid argument: must be a positive int"
# define MALLOC_FAIL "Memory allocation failure\n"
# define THREAD_CREATION_FAIL "Failed to join thread for philosopher %zu\n"
# define THREAD_JOIN_FAIL "Failed to join thread for philosopher %zu\n"
# define THREAD_DETACH_FAIL "Failed to detach thread for philosopher %zu\n"
# define MUTEX_FAIL "Mutex creation failure\n"

/*Logs*/
# define FORK_LOG "\033[1:37m%03lu\033[0m %d has taken a fork\n"
# define EAT_LOG "\033[1:37m%03lu\033[0m %d is eating\n"
# define SLEEP_LOG "\033[1:37m%03lu\033[0m %d is sleeping\n"
# define THINK_LOG "\033[1:37m%03lu\033[0m %d is thinking\n"
# define DEATH_LOG "\033[1:37m%03lu\033[0m \033[1;31m%d died\033[0m\n"
# define ALL_FULL_LOG "\033[1:37m%03lu\033[0m \033[1;32mAll %d philosophers had\
 %d meals\033[0m\n"

/*data_model*/
typedef struct s_philo
{
	size_t			id;
	int				left_fork_id;
	int				right_fork_id;
	__uint64_t		last_meal;
	pthread_mutex_t	last_meal_mutex;
	size_t			nbr_of_meals;
	int				philo_is_full;
	pthread_t		routine;
	struct s_data	*data;
	struct s_philo	*next;
}	t_philo;

typedef struct s_data
{
	size_t			nbr_of_philo;
	__uint64_t		time_to_die;
	__uint64_t		time_to_eat;
	__uint64_t		time_to_sleep;
	size_t			nbr_of_meals;
	int				end_of_simulation;
	pthread_mutex_t	end_of_simulation_mutex;
	size_t			nbr_of_full_philo;
	pthread_mutex_t	nbr_of_full_philo_mutex;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	display_mutex;
	__uint64_t		start_time;
	int				start_of_simulation;
	pthread_mutex_t	start_of_simulation_mutex;
}	t_data;

/*_utils_1.c*/
int		ft_atoi(const char *nptr);
int		ft_isspace(int c);
int		ft_isdigit(int c);
int		ft_isnumeric(char *str);
int		ft_strcmp(const char *s1, const char *s2);

/*_utils_2.c*/
int			ft_min(int a, int b);
int			ft_max(int a, int b);
__uint64_t	get_time(void);
int			display_log(char *log, t_philo *philo);
void		wait_for_start(t_data *data);

/*end.c*/
void	destroy_forks(t_data *data);
void	free_philosopher(t_philo *philosopher);
int		free_data(t_data *data, int exit_code);
int		join_philo_threads(t_data *data);

/*init.c*/
t_philo	*new_philosopher(size_t philo_id, t_data *data);
int		init_philosophers(t_data *data);
int		init_forks(t_data *data);
int		init_data(t_data *data, char **argv);
int		launch_threads(t_data *data);

/*main.c*/
int		check_arguments(int argc, char **argv);
int		main(int argc, char **argv);

/*monitor_routine.c*/
int		philo_is_dead(t_philo *philo);
int		all_full_philo(t_data *data);
void	monitor_routine(t_data *data);

/*philo_routine.c*/
void	takes_forks(t_philo *philo);
void	is_eating(t_philo	*philo);
void	is_sleeping(t_philo *philo);
void	is_thinking(t_philo *philo);
void	*routine(void *void_philo);

#endif