/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src_world_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:13:22 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/06/10 16:27:13 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_init_world(char **av, t_world *w)
{
	w->philo_num = ft_atol(av[1]);
	w->time_die = ft_atol(av[2]);
	w->time_eat = ft_atol(av[3]) * 1000;
	w->time_sleep = ft_atol(av[4]) * 1000;
	w->nbr_limit_meals = -1;
	if (av[5])
		w->nbr_limit_meals = ft_atol(av[5]);
	if (w->nbr_limit_meals == 0)
		ft_error(NULL, "Check number of meals please.", EXIT_FAILURE);
	w->s_fork = ft_sem_open("forks", w->philo_num);
	w->s_ready = ft_sem_open("ready", 0);
	w->s_end = ft_sem_open("end", 0);
	w->s_write = ft_sem_open("write", 1);
	w->philos = ft_mymalloc(sizeof(t_philo) * w->philo_num);
	w->start = ft_gettime(MILI);
}
