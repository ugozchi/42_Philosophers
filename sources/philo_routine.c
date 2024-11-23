/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:18:46 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/23 20:01:18 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void take_forks(t_philo *philo)
{
	int first_fork; 
	int second_fork;

	first_fork = ft_min(philo->left_fork_id, philo->right_fork_id) - 1;
	second_fork = ft_max(philo->left_fork_id, philo->right_fork_id) - 1;
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	display_log(FORK_LOG, philo);

	if (philo->data->nbr_of_philo == 1)
	{
		usleep(philo->data->time_to_die * 1000);
		pthread_mutex_unlock(&philo->data->forks[first_fork]);
		return;
	}
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	display_log(FORK_LOG, philo);
}

int is_full_philo(t_philo *philo)
{
	int philo_is_full;

	pthread_mutex_lock(&philo->nb_meals_mutex);
	philo_is_full = philo->philo_is_full;
	pthread_mutex_unlock(&philo->nb_meals_mutex);

	return (philo_is_full);
}


/* Vérifie la fin de simulation ou si un philosophe est plein */
int check_simulation_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->end_of_simulation_mutex);
	if (philo->data->end_of_simulation)
	{
		pthread_mutex_unlock(&philo->data->end_of_simulation_mutex);
		return (1); // Simulation terminée
	}
	pthread_mutex_unlock(&philo->data->end_of_simulation_mutex);
	if (is_full_philo(philo))
	{
		pthread_mutex_lock(&philo->status_mutex);
		philo->status = THINKING;
		pthread_mutex_unlock(&philo->status_mutex);
		display_log(THINK_LOG, philo);
		return (1); // Philosophe a fini de manger
	}
	return (0);
}

/* Gère les transitions entre les états du philosophe */
void handle_philosopher_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->status_mutex);
	if (philo->status == THINKING && is_full_philo(philo) == 0)
	{
		pthread_mutex_unlock(&philo->status_mutex);
		eating(philo);
	}
	else if (philo->status == EATING)
	{
		pthread_mutex_unlock(&philo->status_mutex);
		sleeping(philo);
	}
	else if (philo->status == SLEEPING)
	{
		pthread_mutex_unlock(&philo->status_mutex);
		thinking(philo);
	}
	else
	{
		pthread_mutex_unlock(&philo->status_mutex);
	}
}

/* Routine principale du philosophe */
void *routine(void *void_philo)
{
	t_philo *philo = (t_philo *)void_philo;

	wait_for_start(philo->data);

	while (1)
	{
		if (check_simulation_end(philo))
			break;
		handle_philosopher_state(philo);
	}
	return (NULL);
}

/*ROUTINE IN 1 BLOC*/
// void *routine(void *void_philo)
// {
// 	t_philo *philo = (t_philo *)void_philo;

// 	wait_for_start(philo->data);

// 	while (1)
// 	{
// 		pthread_mutex_lock(&philo->data->end_of_simulation_mutex);
// 		if (philo->data->end_of_simulation)
// 		{
// 			pthread_mutex_unlock(&philo->data->end_of_simulation_mutex);
// 			break;
// 		}
// 		pthread_mutex_unlock(&philo->data->end_of_simulation_mutex);
// 		if (is_full_philo(philo)) // Vérifie si le philosophe a atteint son quota de repas
// 		{
// 			pthread_mutex_lock(&philo->status_mutex);
// 			philo->status = THINKING;
// 			pthread_mutex_unlock(&philo->status_mutex);
// 			display_log(THINK_LOG, philo);
// 			break;
// 		}
// 		pthread_mutex_lock(&philo->status_mutex);
// 		if (philo->status == THINKING && is_full_philo(philo) == 0)
// 		{
// 			pthread_mutex_unlock(&philo->status_mutex);
// 			eating(philo);
// 		}
// 		else if (philo->status == EATING)
// 		{
// 			pthread_mutex_unlock(&philo->status_mutex);
// 			sleeping(philo);
// 		}
// 		else if (philo->status == SLEEPING)
// 		{
// 			pthread_mutex_unlock(&philo->status_mutex);
// 			thinking(philo);
// 		}
// 		else
// 		{
// 			pthread_mutex_unlock(&philo->status_mutex);
// 		}
// 	}
// 	return (NULL);
// }