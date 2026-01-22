/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haya <haya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:32:14 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/01/21 21:01:02 by haya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n')
	{
		return (1);
	}
	if (c == '\r' || c == '\t' || c == '\v')
	{
		return (1);
	}
	return (0);
}

void skip_spaces(char *str, int *i, int *j)
{
    int index;

    index = 0;
    while (str[index])
    {
        if(isspace(str[*i]))
            (*i)++;
        if(isspace(str[*j]))
            (*j)--;
        if(i == j)
            break;
        index++;
    }
}

static int is_all_num(char *str)
{
    int i;
    int j;

    i = 0;
    j = ft_strlen(str) - 1;
    skip_spaces(str, &i, &j);
	if (str[i] == '+' || str[i] == '-')
		i++;
    while(i <= j)
    {
        if((str[i] < '0' || str[i] > '9'))
            return (0);
        i++;
    }
    return(1);
}

static int args_error(int argc)
{
    if(argc < 5)
        put_err("programm takes more arguments: expected (4 - 5)\n");
    if (argc > 6)
        put_err("too many argumnts programm takes less arguments: expected (4 - 5)\n");
    put_err("Usage : ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
    return(0);
}

int validate_input(int argc, char **argv)
{
    int i;

    if (argc < 5 || argc > 6)
        return args_error(argc);
    i = 1;
    while(argv[i])
    {
        if(!is_all_num(argv[i]))
        {
            put_err("All the inputs should be a valid number\n");
            return (0);
        }
        if(ft_atoi(argv[i]) <= 0)
        {
            put_err("All the inputs should be have number > 0 \n");
            return (0);
        }
        i++;
    }
    return (1);
}

int validate_philo_data(philo_data_t *philo_data)
{
    if (!philo_data->time_mutex || !philo_data->time_of_last_meal || !philo_data->end_mutex || !philo_data->current_eat_count)
    {
        free_philo_data(philo_data);
        return (0);
    }
    return (1);
}
