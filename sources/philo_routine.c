/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:18:46 by uzanchi           #+#    #+#             */
/*   Updated: 2024/10/19 19:11:46 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*Les philosophes commencent toujours  par prender la fourchette avec le plus
petit ID pour évtier une data race*/
void	takes_forks(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	first_fork = ft_min(philo->left_fork_id, philo->right_fork_id) - 1;
	second_fork = ft_max(philo->left_fork_id, philo->right_fork_id) - 1;
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	display_log(FORK_LOG, philo);
	if (philo->data->nbr_of_philo == 1)
	{
		pthread_mutex_unlock(&philo->data->forks[first_fork]);
		return ;
	}
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	display_log(FORK_LOG, philo);
}

/**/
void	is_eating(t_philo	*philo)
{
	takes_forks(philo);
	if (philo->data->nbr_of_philo == 1)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork_id - 1]);
		return ;
	}
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time();
	display_log(EAT_LOG, philo);
	pthread_mutex_unlock(&philo->last_meal_mutex);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork_id - 1]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork_id - 1]);
	philo->nbr_of_meals++;
	if (philo->nbr_of_meals % 3 == 0)
		usleep(200);
	if (philo->data->nbr_of_meals
		&& philo->nbr_of_meals == philo->data->nbr_of_meals
		&& philo->philo_is_full != 1)
	{
		pthread_mutex_lock(&philo->data->nbr_of_full_philo_mutex);
		philo->philo_is_full = 1;
		philo->data->nbr_of_full_philo++;
		pthread_mutex_unlock(&philo->data->nbr_of_full_philo_mutex);
	}
}

/*Puts the philosopher asleep for data->time_to_sleep milliseconds*/
void	is_sleeping(t_philo *philo)
{
	display_log(SLEEP_LOG, philo);
	usleep(philo->data->time_to_sleep * 1000);
}

/*Philosopher starts thinking for a minimal duration of 2 millisecond*/
void	is_thinking(t_philo *philo)
{
	display_log(THINK_LOG, philo);
	usleep(2000);
}

/*Each philosopher starts by eating, before sleeping and then thinking
The edge case of just one philosopher is taken into account to break the
routine (return after trying to eat)*/
void	*routine(void *void_philo)
{
	t_philo	*philo;
	t_data	*data;
	int		end_of_simulation_local;

	philo = (t_philo *)void_philo;
	data = philo->data;
	wait_for_start(data);
	if (philo->id % 2 == 0)
	{
		usleep(200);
		is_thinking(philo);
	}
	while (1)
	{
		pthread_mutex_lock(&data->end_of_simulation_mutex);
		end_of_simulation_local = data->end_of_simulation;
		pthread_mutex_unlock(&data->end_of_simulation_mutex);
		if (end_of_simulation_local)
			break ;
		is_eating(philo);
		if (data->nbr_of_philo == 1)
			break ;
		is_sleeping(philo);
		is_thinking(philo);
	}
	return (NULL);
}
