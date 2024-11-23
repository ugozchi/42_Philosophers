/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:05:44 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/23 19:09:55 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int launch_threads(t_data *data)
{
	size_t i;
	t_philo *ptr;

	i = data->nbr_of_philo;
	ptr = data->philo;
	while (i--)
	{
		if (pthread_create(&ptr->routine, NULL, routine, (void *)ptr) != 0)
		{
			printf(THREAD_CREATION_FAIL, ptr->id);
			while (++i < data->nbr_of_philo)
				pthread_join(ptr->routine, NULL);
			return (EXIT_FAILURE);
		}
		ptr = ptr->next;
	}
	pthread_mutex_lock(&data->display_mutex);
	data->start_time = get_time();
	pthread_mutex_unlock(&data->display_mutex);
	pthread_mutex_lock(&data->start_of_simulation_mutex);
	data->start_of_simulation = 1;
	pthread_mutex_unlock(&data->start_of_simulation_mutex);
	return (EXIT_SUCCESS);
}

/*Boucle parmis tous les philosophes pour rejoinde tous les threads qui ont
été créé*/
int	join_philo_threads(t_data *data)
{
	t_philo	*ptr;
	size_t	i;

	i = data->nbr_of_philo;
	ptr = data->philo;
	while (i--)
	{
		if (pthread_join(ptr->routine, NULL) != 0)
		{
			printf(THREAD_DETACH_FAIL, ptr->id);
			return (EXIT_FAILURE);
		}
		ptr = ptr->next;
	}
	return (EXIT_SUCCESS);
}