/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:18:52 by uzanchi           #+#    #+#             */
/*   Updated: 2024/10/19 18:17:55 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*Checks that the number of arguments is 4 or 5 (excluding program name) and
checks that every argument is a positive integer
Returns 0 if arguments are valid, a positive int if they're not*/
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

/*• Initializes 'start_time' with the time when the process started
• Checks that arguments are valid
• Loads the arguments contained in argv in the structure s_data
• Launches one thread per philosopher for their eat-sleep-think routine
• Launches a monitor routine to check if the simulation should stop (by the
death of a philosopher or because they are all full)
• Properly frees the resources and returns EXIT_SUCCESS*/
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