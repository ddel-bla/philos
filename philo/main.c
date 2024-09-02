/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ddel-bla <ddel-bla@student.42madrid.com	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/20 08:31:34 by ddel-bla		  #+#	#+#			 */
/*   Updated: 2024/05/20 08:31:34 by ddel-bla		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "philo.h"

static void	ft_exit(t_world *world)
{
	int		i;

	i = -1;
	while (++i < world->philo_num)
		pthread_mutex_destroy(&world->philos[i].mtx_philo);
	pthread_mutex_destroy(&world->mtx_print);
	pthread_mutex_destroy(&world->mtx_world);
	free(world->forks);
	free(world->philos);
}

int	main(int ac, char **av)
{
	t_world		world;
	int			i;

	ft_init_world(ac, av, &world);
	ft_init_philos(&world);
	if (world.philo_num == 1)
		pthread_create(&world.philos[0].thread_id, NULL,
			ft_one_thread, &world.philos[0]);
	else
	{
		i = -1;
		while (++i < world.philo_num)
			pthread_create(&world.philos[i].thread_id, NULL,
				ft_init_threads, &world.philos[i]);
	}
	pthread_create(&world.thread_id, NULL, ft_scan_world, &world);
	world.start = ft_gettime(MILI);
	ft_set_b(&world.mtx_world, &world.all_ready, true);
	i = -1;
	while (world.philo_num > ++i)
		pthread_join(world.philos[i].thread_id, NULL);
	ft_set_b(&world.mtx_world, &world.end, true);
	pthread_join(world.thread_id, NULL);
	ft_exit(&world);
	return (0);
}
