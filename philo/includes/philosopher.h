/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:28:25 by haya              #+#    #+#             */
/*   Updated: 2026/01/25 14:34:39 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct philo_s
{
	int				philo_num;
	int64_t			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
}					t_philo;

typedef struct philo_data_s
{
	t_philo			*philo;
	int64_t			*time_of_last_meal;
	int64_t			start_of_simulation;
	pthread_mutex_t	*time_mutex;
	pthread_mutex_t	*end_mutex;
	pthread_mutex_t	*print_mutex;
	int				end_of_simulation;
	int				*current_eat_count;
}					t_philo_data;

typedef struct thread_args_s
{
	int				current_philo;
	int64_t			*current_time_last;
	int64_t			start_of_simulation;
	int				*current_eat_count;
	int				*end_of_simulation;
	pthread_mutex_t	*time_mutex;
	pthread_mutex_t	*end_mutext;
	pthread_mutex_t	*print_mutex;
	int				current_philo_count;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}					t_thread_args;

pthread_t			*create_philos(int philo_num, pthread_mutex_t *forks,
						t_philo *philo, t_philo_data *philo_data);
int					join_philos(int philo_count, pthread_t *philos);
t_philo				*init_philo(char **argv);
pthread_mutex_t		*init_forks(int philo_num);
void				*routine(void *args);
int64_t				calc_time_now(void);
int					create_monitor(pthread_t *monitor,
						t_philo_data *philo_data);
int					ft_atoi(char *str);
void				free_all(t_philo *philo, pthread_t *philos,
						t_philo_data *philo_data);
void				free_philo_data(t_philo_data *philo_data);
void				safe_free(void **place);
t_philo_data		*init_philo_data(t_philo *philo);
void				*ft_calloc(int count, unsigned long size);
int					put_err(char *str);
int					validate_input(int argc, char **argv);
int					ft_strlen(char *str);
int					validate_philo_data(t_philo_data *philo_data);
int					is_end_of_simulation(t_thread_args *c_args);
void				custom_usleep(int64_t micro_sec, t_thread_args *c_args);
void				custom_print(t_thread_args *c_args, char *state);
int					is_all_num(char *str);
void				eat(t_thread_args *c_args);
pthread_mutex_t		*init_malloced_mutext(void);

#endif