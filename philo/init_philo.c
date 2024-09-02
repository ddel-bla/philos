/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   init.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ddel-bla <ddel-bla@student.42madrid.com	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/20 09:08:39 by ddel-bla		  #+#	#+#			 */
/*   Updated: 2024/05/20 09:13:51 by ddel-bla		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "philo.h"

void	ft_init_philos(t_world *world)
{
	int			i;
	t_philo		*philo;

	i = -1;
	while (++i < world->philo_num)
	{
		philo = world->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals = 0;
		pthread_mutex_init(&philo->mtx_philo, NULL);
		philo->world = world;
		philo->first = &world->forks[i];
		philo->second = &world->forks[(i + 1) % world->philo_num];
		if (i % 2)
		{
			philo->second = &world->forks[i];
			philo->first = &world->forks[(i + 1) % world->philo_num];
		}
	}
}
