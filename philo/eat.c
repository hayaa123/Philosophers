/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 12:13:41 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/01/24 12:31:18 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	take_left_right(t_thread_args *c_args)
{
	pthread_mutex_lock(&(c_args->forks[c_args->current_philo]));
	custom_print(c_args, "has taken a fork");
	if (c_args->current_philo == c_args->philo->philo_num - 1)
		pthread_mutex_lock(&(c_args->forks[0]));
	else
		pthread_mutex_lock(&(c_args->forks[c_args->current_philo + 1]));
	custom_print(c_args, "has taken a fork");
}

static void	take_right_left(t_thread_args *c_args)
{
	if (c_args->current_philo == c_args->philo->philo_num - 1)
		pthread_mutex_lock(&(c_args->forks[0]));
	else
		pthread_mutex_lock(&(c_args->forks[c_args->current_philo + 1]));
	custom_print(c_args, "has taken a fork");
	pthread_mutex_lock(&(c_args->forks[c_args->current_philo]));
	custom_print(c_args, "has taken a fork");
}

static void	return_forks(t_thread_args *c_args)
{
	if (c_args->current_philo == c_args->philo->philo_num - 1)
		pthread_mutex_unlock(&(c_args->forks[0]));
	else
		pthread_mutex_unlock(&(c_args->forks[c_args->current_philo + 1]));
	pthread_mutex_unlock(&(c_args->forks[c_args->current_philo]));
}

void	eat(t_thread_args *c_args)
{
	if ((c_args->current_philo + 1) % 2 == 0)
		take_left_right(c_args);
	else
		take_right_left(c_args);
	if (is_end_of_simulation(c_args) == 1)
	{
		return_forks(c_args);
		return ;
	}
	pthread_mutex_lock(c_args->time_mutex);
	*(c_args->current_time_last) = calc_time_now();
	*(c_args->current_eat_count) += 1;
	pthread_mutex_unlock(c_args->time_mutex);
	custom_print(c_args, "eating");
	custom_usleep(c_args->philo->time_to_eat * 1000, c_args);
	return_forks(c_args);
}
