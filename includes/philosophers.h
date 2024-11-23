/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:52:05 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/23 19:59:32 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

/*******************************LIBRARIES*************************************/

#include "message.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>


/*****************************DATA_STRUCTURE**********************************/

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	DIED
} t_philo_status;

typedef struct s_philo
{
	size_t id;
	int left_fork_id;
	int right_fork_id;
	__uint64_t last_meal;
	size_t nbr_of_meals;
	int philo_is_full;

	t_philo_status status;

	pthread_t routine;

	pthread_mutex_t last_meal_mutex;
	pthread_mutex_t status_mutex;
	pthread_mutex_t nb_meals_mutex;

	struct s_data *data;
	struct s_philo *next;
} t_philo;

typedef struct s_data
{
	__uint64_t start_time;
	int start_of_simulation;
	int end_of_simulation;

	size_t nbr_of_philo;
	__uint64_t time_to_die;
	__uint64_t time_to_eat;
	__uint64_t time_to_sleep;
	size_t nbr_of_meals;
	size_t nbr_of_full_philo;

	t_philo *philo;

	pthread_mutex_t end_of_simulation_mutex;
	pthread_mutex_t nbr_of_full_philo_mutex;
	pthread_mutex_t *forks;
	pthread_mutex_t display_mutex;
	pthread_mutex_t start_of_simulation_mutex;
} t_data;

/*******************************FUNCTIONS*************************************/

/*cherckers_utils.c*/
int ft_atoi(const char *nptr);
int ft_isspace(int c);
int ft_isdigit(int c);
int ft_isnumeric(char *str);
int ft_strcmp(const char *s1, const char *s2);

/*clean.c*/
void destroy_forks(t_data *data);
void free_philosopher(t_philo *philosopher);
int free_data(t_data *data, int exit_code);

/*global_utils.c*/
int ft_min(int a, int b);
int ft_max(int a, int b);
__uint64_t get_time(void);
int display_log(char *log, t_philo *philo);

/*init.c*/
t_philo *new_philosopher(size_t philo_id, t_data *data);
int init_philosophers(t_data *data);
int init_forks(t_data *data);
int init_data(t_data *data, char **argv);
t_philo_status get_initial_status(size_t id, size_t nbr_of_philo);

/*main.c*/
int check_arguments(int argc, char **argv);
int main(int argc, char **argv);

/*monitor_routine.c*/
int philo_is_dead(t_philo *philo);
int all_full_philo(t_data *data);
void wait_for_start(t_data *data);
int check_end_conditions(t_data *data, t_philo *philo);
void monitor_routine(t_data *data);

/*philo_routine.c*/
void take_forks(t_philo *philo);
int is_full_philo(t_philo *philo);
int check_simulation_end(t_philo *philo);
void handle_philosopher_state(t_philo *philo);
void *routine(void *void_philo);

/*state.c*/
void eating(t_philo *philo);
void sleeping(t_philo *philo);
void thinking(t_philo *philo);

/*thread.c*/
int launch_threads(t_data *data);
int join_philo_threads(t_data *data);



#endif