/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:13:09 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/06/06 12:13:09 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_exit(t_world *world)
{
	int	i;

	i = 0;
	while (i < world->philo_num)
		kill(world->philos[i++].pid, SIGKILL);
	ft_sem_close(world->s_fork);
	ft_sem_unlink("forks");
	ft_sem_close(world->s_ready);
	ft_sem_unlink("ready");
	ft_sem_close(world->s_end);
	ft_sem_unlink("end");
	ft_sem_close(world->s_write);
	ft_sem_unlink("write");
	free(world->philos);
}

int	main(int ac, char **av)
{
	t_world		world;
	int			i;
	pthread_t	monitor;

	if (ac != 5 && ac != 6)
		return (printf("Please enter ./philo XXX XXX XXX [X]\n"), EXIT_FAILURE);
	ft_init_world(av, &world);
	i = -1;
	while (++i < world.philo_num)
	{
		ft_init_philo(&world, i);
		//usleep(50);
	}
	while (--i > -1)
		ft_sem_post(world.s_ready);
	pthread_create(&monitor, NULL, ft_scan_f_alive, &world);
	pthread_detach(monitor);
	ft_sem_wait(world.s_end);
	ft_exit(&world);
	return (EXIT_SUCCESS);
}
