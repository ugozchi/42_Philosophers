/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:18:52 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/23 19:05:15 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_arguments(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (printf(WRG_ARG_NR));
	i = 1;
	while (argv[i])
	{
		if (!ft_isnumeric(argv[i]) || ft_atoi(argv[i]) <= 0)
			return (printf(INVALID_ARG, argv[i]));
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_arguments(argc, argv))
		return (EXIT_FAILURE);
	if (init_data(&data, argv))
		return (free_data(&data, EXIT_FAILURE));
	if (launch_threads(&data))
		return (free_data(&data, EXIT_FAILURE));
	monitor_routine(&data);
	join_philo_threads(&data);
	return (free_data(&data, EXIT_SUCCESS));
}
