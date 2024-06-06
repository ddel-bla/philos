/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_scan_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:14:51 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/06/06 17:03:12 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_scan_f_die(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->next_meal < ft_gettime(MILI))
		{
			ft_write_log(DIED, philo);
			sem_post(philo->world->s_end);
			break ;
		}
		usleep(200);
	}
	return (NULL);
}

void	*ft_scan_f_alive(void *arg)
{
	t_world	*world;
	int		i;

	world = (t_world *)arg;
	i = -1;
	while (++i < world->philo_num)
		waitpid(world->philos[i].pid, NULL, 0);
	sem_post(world->s_end);
	return (NULL);
}
