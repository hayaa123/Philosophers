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
    philo_t philo;
    pthread_t *philos;
    pthread_mutex_t *forks;

    if(argc < 1 || argc > 6)
        return(1);
    init_philo(&philo, argv);
    forks = init_forks(philo.philo_num);
    philos = create_philos(philo.philo_num, forks, philo);
    if(join_philos(philo.philo_num, philos) != 0 )
        return (3);
    free(philos);
    destroy_forks(philo.philo_num, forks);
}
