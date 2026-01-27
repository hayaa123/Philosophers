/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:32:14 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/01/24 13:17:37 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	args_error(int argc)
{
	if (argc < 5)
		put_err("programm takes more arguments: expected (4 - 5)\n");
	if (argc > 6)
	{
		put_err("too many argumnts: expected (4 - 5)\n");
	}
	put_err("Usage : ./philo number_of_philosophers");
	put_err("time_to_die time_to_eat time_to_sleep");
	put_err("[number_of_times_each_philosopher_must_eat]\n");
	return (0);
}

int	validate_input(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (args_error(argc));
	i = 1;
	while (argv[i])
	{
		if (!is_all_num(argv[i]))
		{
			put_err("All the inputs should be a valid number\n");
			return (0);
		}
		if (ft_atoi(argv[i]) <= 0)
		{
			put_err("All the inputs should be have number > 0 \n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	validate_philo_data(t_philo_data *philo_data)
{
	if (!philo_data->time_mutex || !philo_data->time_of_last_meal
		|| !philo_data->end_mutex || !philo_data->current_eat_count)
	{
		free_philo_data(philo_data);
		return (0);
	}
	return (1);
}
