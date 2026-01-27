/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:50:48 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/01/25 14:32:12 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	destroy_forks(int philo_num, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (!forks)
		return ;
	while (i < philo_num)
	{
		pthread_mutex_destroy(&(forks[i]));
		i++;
	}
	free(forks);
}

int	free_return(t_philo *philo, pthread_t *philos, t_philo_data *philo_data,
		pthread_mutex_t *forks)
{
	destroy_forks(philo->philo_num, forks);
	free_all(philo, philos, philo_data);
	put_err("something went wrong :(\n");
	return (1);
}

int	wait_monitor_free(t_philo_data *philo_data, pthread_t monitor,
		t_philo *philo, pthread_mutex_t *forks)
{
	philo_data->end_of_simulation = 1;
	pthread_join(monitor, NULL);
	return (free_return(philo, NULL, philo_data, forks));
}

int	exit_code(t_philo *philo, pthread_mutex_t *forks, pthread_t *philos,
		t_philo_data *philo_data)
{
	destroy_forks(philo->philo_num, forks);
	free_all(philo, philos, philo_data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	pthread_t		monitor;
	t_philo_data	*philo_data;

	if (!validate_input(argc, argv))
		return (1);
	philo = init_philo(argv);
	if (!philo)
		return (put_err("something went wrong :(\n"));
	forks = init_forks(philo->philo_num);
	philo_data = init_philo_data(philo);
	if (!philo_data || !forks)
		return (free_return(philo, NULL, philo_data, forks));
	if (create_monitor(&monitor, philo_data) == 1)
		return (free_return(philo, NULL, philo_data, forks));
	philos = create_philos(philo->philo_num, forks, philo, philo_data);
	if (!philos)
		return (wait_monitor_free(philo_data, monitor, philo, forks));
	if (join_philos(philo->philo_num, philos) != 0)
		return (wait_monitor_free(philo_data, monitor, philo, forks));
	if (pthread_join(monitor, NULL) != 0)
		return (free_return(philo, philos, philo_data, forks));
	return (exit_code(philo, forks, philos, philo_data));
}
