/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:23:43 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/23 19:32:41 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void eating(t_philo *philo)
{
	take_forks(philo); // Le philosophe essaie de prendre deux fourchettes
	if (philo->data->nbr_of_philo == 1)
		return;
	pthread_mutex_lock(&philo->status_mutex);
	philo->status = EATING;
	pthread_mutex_unlock(&philo->status_mutex);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	display_log(EAT_LOG, philo);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork_id - 1]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork_id - 1]);
	pthread_mutex_lock(&philo->nb_meals_mutex);
	philo->nbr_of_meals++;
	if (philo->data->nbr_of_meals > 0 && philo->nbr_of_meals >= philo->data->nbr_of_meals)
	{
		philo->philo_is_full = 1;
		pthread_mutex_lock(&philo->data->nbr_of_full_philo_mutex);
		philo->data->nbr_of_full_philo++;
		pthread_mutex_unlock(&philo->data->nbr_of_full_philo_mutex);
	}
	pthread_mutex_unlock(&philo->nb_meals_mutex);
}

void sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->status_mutex);
	philo->status = SLEEPING;
	pthread_mutex_unlock(&philo->status_mutex);

	display_log(SLEEP_LOG, philo);
	usleep(philo->data->time_to_sleep * 1000);
}

void thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->status_mutex);
	philo->status = THINKING;
	pthread_mutex_unlock(&philo->status_mutex);

	display_log(THINK_LOG, philo);
	usleep(2000); // Temps minimal avant de tenter de prendre les fourchettes
}
