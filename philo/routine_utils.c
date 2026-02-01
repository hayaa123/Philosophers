/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haya <haya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:58:23 by haya              #+#    #+#             */
/*   Updated: 2026/02/01 16:52:31 by haya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	is_end_of_simulation(t_thread_args *c_args)
{
	pthread_mutex_lock(c_args->end_mutext);
	if (*(c_args->end_of_simulation) == 1)
	{
		pthread_mutex_unlock(c_args->end_mutext);
		return (1);
	}
	pthread_mutex_unlock(c_args->end_mutext);
	return (0);
}

void	custom_usleep(int64_t micro_sec, t_thread_args *c_args)
{
	int64_t	start_time;

	start_time = calc_time_now();
	while ((calc_time_now() - start_time) * 1000 < micro_sec)
	{
		if (is_end_of_simulation(c_args) == 1)
			break ;
		usleep(500);
	}
}

void	custom_print(t_thread_args *c_args, char *state)
{
	pthread_mutex_lock(c_args->print_mutex);
	if (is_end_of_simulation(c_args) == 1)
	{
		pthread_mutex_unlock(c_args->print_mutex);
		return ;
	}
	printf("%lu %i %s\n", calc_time_now() - c_args->start_of_simulation,
		c_args->current_philo + 1, state);
	pthread_mutex_unlock(c_args->print_mutex);
}
