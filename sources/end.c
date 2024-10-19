/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:14:41 by uzanchi           #+#    #+#             */
/*   Updated: 2024/10/19 18:23:18 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

/*Detruit tous les mutex pour les fourchettes et free le pointeur forks*/
void	destroy_forks(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nbr_of_philo)
		pthread_mutex_destroy(&data->forks[i++]);
	free(data->forks);
}

/*Free toutes la memoire alloue pour un philosophe*/
void	free_philosopher(t_philo *philosopher)
{
	if (!philosopher)
		return ;
	pthread_mutex_destroy(&philosopher->last_meal_mutex);
	free(philosopher);
	philosopher = NULL;
}

/*Boucle parmis les philosophes contenue dans data->philo et free
la memoire alloue*/
int	free_data(t_data *data, int exit_code)
{
	t_philo	*first;
	t_philo	*current;
	t_philo	*next;

	destroy_forks(data);
	pthread_mutex_destroy(&data->nbr_of_full_philo_mutex);
	pthread_mutex_destroy(&data->display_mutex);
	pthread_mutex_destroy(&data->end_of_simulation_mutex);
	pthread_mutex_destroy(&data->start_of_simulation_mutex);
	current = data->philo;
	if (!current)
		return (exit_code);
	first = current;
	next = current->next;
	while (current && next != first)
	{
		free_philosopher(current);
		current = next;
		if (current)
			next = current->next;
	}
	if (current)
		free_philosopher(current);
	return (exit_code);
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
