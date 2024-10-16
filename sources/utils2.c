/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:12:28 by uzanchi           #+#    #+#             */
/*   Updated: 2024/10/16 14:06:25 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    ft_min(int a, int b)
{
    if (a < b)
        return (a);
    return (b);
}

int    ft_max(int a, int b)
{
    if (a >= b)
        return (a);
    return (b);
}

clock_t get_time(void)
{
    struct timeval  time;
    clock_t         output;

    gettimeofday(&time, NULL);
	output = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (output);
}

int display_log(char *log, t_philo *philo)
{
    
}