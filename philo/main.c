#include "philosopher.h"

void destroy_forks(int philo_num, pthread_mutex_t *forks)
{
    int i;

    i = 0;
    while(i < philo_num)
    {
        pthread_mutex_destroy(&(forks[i]));
        i++;
    }
    free(forks);
}


int main(int argc, char **argv)
{
    philo_t *philo;
    pthread_t *philos;
    pthread_mutex_t *forks;
    pthread_t monitor;
    philo_data_t *philo_data;

    if(argc < 1 || argc > 6)
        return(1);
    philo = init_philo(argv);
    forks = init_forks(philo->philo_num);
    philo_data = init_philo_data(philo);
    if(create_monitor(&monitor, philo_data) == 1)
        return (2);
    philos = create_philos(philo->philo_num, forks, philo, philo_data);
    if(!philos)
        return(3);
    if(join_philos(philo->philo_num, philos) != 0 )
        return (4);
    if (pthread_join(monitor, NULL) != 0)
        return (5);
    free_all(philo, philos, philo_data);
    destroy_forks(philo->philo_num, forks);
}
