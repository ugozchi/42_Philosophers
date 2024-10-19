/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:19:22 by uzanchi           #+#    #+#             */
/*   Updated: 2024/10/19 16:36:11 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
/*Compare le temps entre le dernier repas et le temps actuel. Si la différence
est superieur à time_to_die, alors le philosophe est mort et la fonction
retourne 1*/
int	philo_is_dead(t_philo *philo)
{
	clock_t time_since_last_meal;

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
	
}