/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:13:27 by uzanchi           #+#    #+#             */
/*   Updated: 2024/10/19 19:20:44 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*Alloue de la memoire et inialise un nouveau philosopher avec les ID de ses
fourchettes. Mais aussi la date du dernier repas(debut de la simulation) */
t_philo	*new_philosopher(size_t philo_id, t_data *data)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
	{
		printf(MALLOC_FAIL);
		return (NULL);
	}
	new->id = philo_id;
	new->left_fork_id = philo_id;
	new->right_fork_id = philo_id + 1;
	if (pthread_mutex_init(&new->last_meal_mutex, NULL))
	{
		printf(MUTEX_FAIL);
		return (NULL);
	}
	new->nbr_of_meals = 0;
	new->philo_is_full = 0;
	new->data = data;
	new->last_meal = get_time();
	return (new);
}

/*Initialise la liste de tous les philosophes en liste circulaire. Le premier
et dernier philosophe sont assis a cote. et partage une fourchette.
Si la creation d'un seul echoue, la focntion retourne EXIT_FAILURE*/
int	init_philosophers(t_data *data)
{
	t_philo	*ptr;
	size_t	philo_id;

	data->philo = new_philosopher(1, data);
	if (!data->philo)
		return (EXIT_FAILURE);
	ptr = data->philo;
	philo_id = 2;
	while (philo_id <= data->nbr_of_philo)
	{
		ptr->next = new_philosopher(philo_id++, data);
		if (!ptr->next)
			return (EXIT_FAILURE);
		ptr = ptr->next;
	}
	ptr->right_fork_id = 1;
	ptr->next = data->philo;
	return (EXIT_SUCCESS);
}

/*Initialisation des mutex pour chacune des fourchettes.
EXIT_FAILURE si l'une des initialisations fail*/
int	init_forks(t_data *data)
{
	size_t	i;

	data->forks = malloc(data->nbr_of_philo * sizeof(pthread_mutex_t));
	if (!data->forks)
	{
		printf(MALLOC_FAIL);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < data->nbr_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			printf(MUTEX_FAIL);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

/*Initialise la data avec les arguments, puis initialise les philosophes
et leurs fourchettes*/
int	init_data(t_data *data, char **argv)
{
	data->nbr_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->nbr_of_meals = ft_atoi(argv[5]);
	else
		data->nbr_of_meals = 0;
	data->end_of_simulation = 0;
	data->start_of_simulation = 0;
	data->nbr_of_full_philo = 0;
	if (init_philosophers(data))
		return (free_data(data, EXIT_FAILURE));
	if (init_forks(data))
		return (free_data(data, EXIT_FAILURE));
	if (pthread_mutex_init(&data->nbr_of_full_philo_mutex, NULL)
		|| pthread_mutex_init(&data->display_mutex, NULL)
		|| pthread_mutex_init(&data->end_of_simulation_mutex, NULL)
		|| pthread_mutex_init(&data->start_of_simulation_mutex, NULL))
		return (free_data(data, EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

/*Boucle le temps qu'un thread soit envoye pour chacun des philosophes.*/
int	launch_threads(t_data *data)
{
	size_t	i;
	t_philo	*ptr;

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
