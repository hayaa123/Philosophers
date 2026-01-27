/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:10:00 by haya              #+#    #+#             */
/*   Updated: 2026/01/27 13:43:57 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	one_philo_routine(t_thread_args	*c_args)
{
	pthread_mutex_lock(&(c_args->forks[0]));
	custom_print(c_args, "has taken a fork");
	custom_usleep(c_args->philo->time_to_die, c_args);
	pthread_mutex_unlock(&(c_args->forks[0]));
}

static void	sleep_and_think(t_thread_args	*c_args)
{
	custom_print(c_args, "sleeping");
	custom_usleep(c_args->philo->time_to_sleep * 1000, c_args);
	custom_print(c_args, "thinking");
	custom_usleep(3000, c_args);
}

void	*routine(void *args)
{
	t_thread_args	*c_args;

	c_args = (t_thread_args *)args;
	if ((c_args->current_philo + 1) % 2 == 0)
		usleep(100);
	pthread_mutex_lock(c_args->time_mutex);
	*(c_args->current_time_last) = calc_time_now();
	pthread_mutex_unlock(c_args->time_mutex);
	while (1)
	{
		if (c_args->philo->philo_num == 1)
		{
			one_philo_routine(c_args);
			break ;
		}
		if (is_end_of_simulation(c_args) == 1)
			break ;
		eat(c_args);
		if (is_end_of_simulation(c_args) == 1)
			break ;
		sleep_and_think(c_args);
	}
	free(args);
	return (NULL);
}
