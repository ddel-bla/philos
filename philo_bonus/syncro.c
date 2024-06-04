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

bool	ft_check(t_philo *philo)
{
	//REVISAR HACIENDO UN SOLO RETURN
	if (ft_finished(philo->world))
		return (1);
	if (ft_philo_died(philo))
	{
		ft_write_log(DIED, philo);
		if (sem_wait(philo->world->s_end) == -1)
			ft_error("sem_wait s_end failed");
		philo->world->end = true;
		if (sem_post(philo->world->s_end) == -1)
			ft_error("sem_post s_end failed");
		return (1);
	}
	return (0);
}
bool	ft_finished(t_world *world)
{
	bool	ret;

	if (sem_wait(world->s_end) == -1)
		ft_error("sem_wait s_end failed");
	ret = world->end;
	if (sem_post(world->s_end) == -1)
		ft_error("sem_post s_end failed");
	return (ret);
}

bool	ft_philo_died(t_philo *philo)
{
	long	elapsed;

	if (!philo->meals)
		return (0);
	elapsed = ft_gettime(MILI) - philo->last_meal;
	if (elapsed > philo->world->time_die)
		return (1);
	return (0);
}
void	ft_scan_world(t_world *world)
{
	int			i;

	i = 1;
	while (!ft_finished(world))
	{
		i = -1;
		while (++i < world->philo_num && !ft_finished(world))
		{
			//printf("!ft_finished(world))            %i\n", !ft_finished(world));
			//printf("ft_philo_died(&world->philos[i] %i\n", ft_philo_died(&world->philos[i]));
			if (ft_philo_died(&world->philos[i]))
			{
				world->end = true;
				ft_write_log(DIED, &world->philos[i]);
			}
		}
	}
}
