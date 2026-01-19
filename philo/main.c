#include "philosopher.h"

void destroy_forks(int philo_num, pthread_mutex_t *forks)
{
    int i;

    i = 0;
    while (i < philo_num)
    {
        pthread_mutex_destroy(&(forks[i]));
        i++;
    }
    free(forks);
}

int free_return(philo_t *philo, pthread_t *philos, philo_data_t *philo_data, pthread_mutex_t *forks)
{
    free_all(philo, philos, philo_data);
    destroy_forks(philo->philo_num, forks);
    put_err("something went wrong :(\n");
    return (1);
}


int main(int argc, char **argv)
{
    philo_t *philo;
    pthread_t *philos;
    pthread_mutex_t *forks;
    pthread_t monitor;
    philo_data_t *philo_data;

    if (!validate_input(argc, argv))
        return (1);
    philo = init_philo(argv);
    forks = init_forks(philo->philo_num);
    philo_data = init_philo_data(philo);
    if (philo_data == NULL)
        return (free_return(philo, NULL, philo_data, forks));
    if (create_monitor(&monitor, philo_data) == 1)
        return (free_return(philo, NULL, philo_data, forks));
    philos = create_philos(philo->philo_num, forks, philo, philo_data);
    if (!philos)
        return (free_return(philo, NULL, philo_data, forks));
    if (join_philos(philo->philo_num, philos) != 0)
        return (free_return(philo, philos, philo_data, forks));
    if (pthread_join(monitor, NULL) != 0)
        return (free_return(philo, philos, philo_data, forks));
    free_all(philo, philos, philo_data);
    return (0);
}
