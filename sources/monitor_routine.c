/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:19:22 by uzanchi           #+#    #+#             */
/*   Updated: 2024/10/19 19:15:43 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
/*Compare le temps entre le dernier repas et le temps actuel. Si la différence
est superieur à time_to_die, alors le philosophe est mort et la fonction
retourne 1*/
int	philo_is_dead(t_philo *philo)
{
	__uint64_t	time_since_last_meal;

	pthread_mutex_lock(&philo->last_meal_mutex);
	time_since_last_meal = get_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (time_since_last_meal > philo->data->time_to_die)
		return (1);
	return (0);
}

/*Regarde si le nombre de full philosophe dans la structure s_data est égale
au nombre de philosophe dans la simulation. Retourne 1 si full*/
int	all_full_philo(t_data *data)
{
	if (!data->nbr_of_meals)
		return (0);
	pthread_mutex_lock(&data->nbr_of_full_philo_mutex);
	if (data->nbr_of_full_philo == data->nbr_of_philo)
	{
		pthread_mutex_unlock(&data->nbr_of_full_philo_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->nbr_of_full_philo_mutex);
	return (0);
}

/*Regarde toutes les 10 microsecondes si tous les philosophes ont mangés
ou si l'un est mort. Si c'est le cas la routine termine et retourne NULL*/
void	monitor_routine(t_data *data)
{
	t_philo	*philo;

	wait_for_start(data);
	philo = data->philo;
	while (1)
	{
		if (philo_is_dead(philo) || all_full_philo(data))
		{
			pthread_mutex_lock(&philo->data->end_of_simulation_mutex);
			data->end_of_simulation = 1;
			pthread_mutex_unlock(&philo->data->end_of_simulation_mutex);
			if (all_full_philo(data))
				display_log(ALL_FULL_LOG, philo);
			else
				display_log(DEATH_LOG, philo);
			break ;
		}
		philo = philo->next;
		usleep(50);
	}
}