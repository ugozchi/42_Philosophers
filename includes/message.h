/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:35:04 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/23 19:38:26 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_H
# define MESSAGE_H

/*Errors*/
#define WRG_ARG_NR "The program expects 4 or 5 arguments: \
number_of_philosophers, time_to_die, time_to_eat, time_to_sleep and \
number_of_times_each_philosopher_must_eat (optional)\n"
#define INVALID_ARG "%s is an invalid argument: must be a positive int"
#define MALLOC_FAIL "Memory allocation failure\n"
#define THREAD_CREATION_FAIL "Failed to join thread for philosopher %zu\n"
#define THREAD_JOIN_FAIL "Failed to join thread for philosopher %zu\n"
#define THREAD_DETACH_FAIL "Failed to detach thread for philosopher %zu\n"
#define MUTEX_FAIL "Mutex creation failure\n"

/*Logs*/
#define FORK_LOG "\033[1:37m%03lu\033[0m %d has taken a fork\n"
#define EAT_LOG "\033[1:37m%03lu\033[0m %d is eating\n"
#define SLEEP_LOG "\033[1:37m%03lu\033[0m %d is sleeping\n"
#define THINK_LOG "\033[1:37m%03lu\033[0m %d is thinking\n"
#define DEATH_LOG "\033[1:37m%03lu\033[0m \033[1;31m%d died\033[0m\n"
#define ALL_FULL_LOG "\033[1:37m%03lu\033[0m \033[1;32mAll %d philosophers had\
 %d meals\033[0m\n"

#endif