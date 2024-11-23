/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:19:22 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/23 19:49:36 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Vérifie si un philosophe est mort */
int philo_is_dead(t_philo *philo)
{
	__uint64_t time_since_last_meal;

	pthread_mutex_lock(&philo->last_meal_mutex);
	time_since_last_meal = get_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);

	return (time_since_last_meal > philo->data->time_to_die);
	/* Si le return ne passe pas, go en dessous
	if (time_since_last_meal > philo->data->time_to_die)
		return (1);
	return (0)*/
}

/* Vérifie si tous les philosophes sont "pleins" */
int all_full_philo(t_data *data)
{
	int is_all_full;

	pthread_mutex_lock(&data->nbr_of_full_philo_mutex);
	is_all_full = (data->nbr_of_full_philo == data->nbr_of_philo);
	pthread_mutex_unlock(&data->nbr_of_full_philo_mutex);

	return (is_all_full);
}

/*Boucle en attendant le flag pour commencer*/
void	wait_for_start(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->start_of_simulation_mutex);
		if (data->start_of_simulation)
			break ;
		pthread_mutex_unlock(&data->start_of_simulation_mutex);
		usleep(500);
	}
	pthread_mutex_unlock(&data->start_of_simulation_mutex);
}

int	check_end_conditions(t_data *data, t_philo *philo)
{
	if (philo_is_dead(philo))
	{
		pthread_mutex_lock(&data->end_of_simulation_mutex);
		data->end_of_simulation = 1;
		pthread_mutex_unlock(&data->end_of_simulation_mutex);
		display_log(DEATH_LOG, philo);
		return (1);
	}
	if (all_full_philo(data))
	{
		pthread_mutex_lock(&data->end_of_simulation_mutex);
		data->end_of_simulation = 1;
		pthread_mutex_unlock(&data->end_of_simulation_mutex);
		display_log(ALL_FULL_LOG, philo);
		return (1);
	}
	return (0);
}

/* Routine de surveillance */
void monitor_routine(t_data *data)
{
	t_philo *philo;

	wait_for_start(data);
	while (1)
	{
		philo = data->philo;
		while (philo)
		{
			if (check_end_conditions(data, philo))
				return;
			philo = philo->next;
			if (philo == data->philo)
				break;
		}
		// usleep(100); // Evite une surcharge CPU
	}
}

/* FONCTION MONITOR EN 1 BLOC
void monitor_routine(t_data *data)
{
	t_philo *philo;

	wait_for_start(data);
	while (1)
	{
		philo = data->philo;
		while (philo)
		{
			if (philo_is_dead(philo))
			{
				pthread_mutex_lock(&data->end_of_simulation_mutex);
				data->end_of_simulation = 1;
				pthread_mutex_unlock(&data->end_of_simulation_mutex);
				display_log(DEATH_LOG, philo);
				return;
			}
			if (all_full_philo(data))
			{
				pthread_mutex_lock(&data->end_of_simulation_mutex);
				data->end_of_simulation = 1;
				pthread_mutex_unlock(&data->end_of_simulation_mutex);
				display_log(ALL_FULL_LOG, philo);
				return;
			}
			philo = philo->next;
			if (philo == data->philo)
				break;
		}
		// usleep(100); // Evite une surcharge CPU
	}
}*/
