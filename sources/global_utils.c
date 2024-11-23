/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:12:28 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/23 19:19:26 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int	ft_max(int a, int b)
{
	if (a >= b)
		return (a);
	else
		return (b);
}

__uint64_t	get_time(void)
{
	struct timeval	time;
	__uint64_t			output;

	gettimeofday(&time, NULL);
	output = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (output);
}

/*Displays the log passed as a string pointer for the philosopher 'philo'*/
int	display_log(char *log, t_philo *philo)
{
	__uint64_t	timestamp;
	int		end_of_simulation_local;

	pthread_mutex_lock(&philo->data->end_of_simulation_mutex);
	end_of_simulation_local = philo->data->end_of_simulation;
	pthread_mutex_unlock(&philo->data->end_of_simulation_mutex);
	if (end_of_simulation_local && ft_strcmp(log, ALL_FULL_LOG)
		&& ft_strcmp(log, DEATH_LOG))
		return (0);
	pthread_mutex_lock(&philo->data->display_mutex);
	timestamp = get_time() - philo->data->start_time;
	if (ft_strcmp(log, ALL_FULL_LOG) == 0)
		printf(log, timestamp, philo->data->nbr_of_philo,
			philo->data->nbr_of_meals);
	else
		printf(log, timestamp, philo->id);
	pthread_mutex_unlock(&philo->data->display_mutex);
	return (1);
}

