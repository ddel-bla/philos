/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parseworld.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ddel-bla <ddel-bla@student.42madrid.com	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/21 08:31:02 by ddel-bla		  #+#	#+#			 */
/*   Updated: 2024/05/21 08:31:43 by ddel-bla		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "philo.h"

void	ft_init_world(t_world *world, long p[5])
{
	int	i;

	world->philo_num = p[0];
	world->time_die = p[1];
	world->time_eat = p[2];
	world->time_sleep = p[3];
	world->nbr_limit_meals = p[4];
	world->philo_threads = 0;
	world->end = false;
	world->all_ready = false;
	world->philos = ft_mymalloc(sizeof(t_philo) * world->philo_num);
	world->forks = ft_mymalloc(sizeof(t_fork) * world->philo_num);
	pthread_mutex_init(&world->mtx_world, NULL);
	pthread_mutex_init(&world->mtx_print, NULL);
	i = -1;
	while (++i < world->philo_num)
	{
		pthread_mutex_init(&world->forks[i].mtx_fork, NULL);
		world->forks[i].fork_id = i;
	}
}
