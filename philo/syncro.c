/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   syncro.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ddel-bla <ddel-bla@student.42madrid.com	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/21 08:56:22 by ddel-bla		  #+#	#+#			 */
/*   Updated: 2024/05/23 06:57:45 by ddel-bla		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "philo.h"

static bool	ft_philo_died(t_philo *philo)
{
	long	elapsed;

	if (ft_get_b(&philo->mtx_philo, &philo->full))
		return (0);
	elapsed = ft_gettime(MILI) - ft_get_l(&philo->mtx_philo, &philo->last_meal);
	if (elapsed > philo->world->time_die)
		return (1);
	return (0);
}

void	ft_wait_all_threads(t_world *world)
{
	while (ft_get_b(&world->mtx_world, &world->all_ready) == false)
		;
}

bool	ft_finished(t_world *world)
{
	return (ft_get_b(&world->mtx_world, &world->end));
}

void	*ft_scan_world(void	*data)
{
	t_world		*world;
	int			i;

	world = (t_world *) data;
	i = 1;
	while (i == 1)
	{
		pthread_mutex_lock(&world->mtx_world);
		if (world->philo_num == world->philo_threads)
			i = -1;
		pthread_mutex_unlock(&world->mtx_world);
	}
	while (!ft_finished(world))
	{
		i = -1;
		while (++i < world->philo_num && !ft_finished(world))
		{
			if (ft_philo_died(&world->philos[i]))
			{
				ft_set_b(&world->mtx_world, &world->end, true);
				ft_write_log(DIED, &world->philos[i]);
			}
		}
	}
	return (NULL);
}
