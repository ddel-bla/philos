/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src_philo_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:13:39 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/06/10 19:10:28 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_init_dinner(t_philo *philo)
{
	pthread_t	monitor;

	pthread_create(&monitor, NULL, ft_scan_f_die, philo);
	pthread_detach(monitor);
	while (1)
	{
		ft_eat(philo);
		if (philo->meals == 0)
			break ;
		ft_sleep(philo);
		ft_thinking(philo);
	}
}

void	ft_init_philo(t_world *world, int i)
{
	t_philo		*philo;
	char		*str;

	philo = world->philos + i;
	philo->id = i + 1;
	philo->meals = world->nbr_limit_meals;
	philo->world = world;
	philo->die_time = world->time_die;
	philo->next_meal = world->start + philo->die_time;
	philo->impar = (world->philo_num % 2);
	str = ft_itoa(philo->id);
	philo->s_philo = ft_sem_open(str, 1);
	free(str);
	philo->pid = ft_myfork();
	if (philo->pid == 0)
	{
		if (philo->id % 2 == 0)
			ft_delaying(philo, 1);
		ft_init_dinner(philo);
		exit(0);
	}
}

void	ft_one_philo(t_world *world, int i)
{
	t_philo		*philo;
	char		*str;
	pthread_t	monitor;

	philo = world->philos + i;
	philo->id = i + 1;
	philo->meals = world->nbr_limit_meals;
	philo->world = world;
	philo->die_time = world->time_die;
	philo->next_meal = world->start + philo->die_time;
	str = ft_itoa(philo->id);
	philo->s_philo = ft_sem_open(str, 1);
	free(str);
	philo->pid = ft_myfork();
	if (philo->pid == 0)
	{
		pthread_create(&monitor, NULL, ft_scan_f_die, philo);
		pthread_detach(monitor);
		ft_write_log(FORK, philo);
		while (1)
			ft_myusleep(50);
	}
}
