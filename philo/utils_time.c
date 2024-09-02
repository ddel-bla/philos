/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   utils.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ddel-bla <ddel-bla@student.42madrid.com	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/20 08:31:46 by ddel-bla		  #+#	#+#			 */
/*   Updated: 2024/05/20 08:31:46 by ddel-bla		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "philo.h"

long	ft_gettime(t_time timecode)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		printf("Gettimeofday failed\n");
	if (MILI == timecode)
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	else
		return (tv.tv_sec * 1000000 + tv.tv_usec);
}

void	ft_myusleep(long usec, t_world *world)
{
	long	start;
	long	current;
	long	left;

	start = ft_gettime(MICRO);
	while (ft_gettime(MICRO)- start < usec)
	{
		if (ft_finished(world))
			break ;
		current = ft_gettime(MICRO) - start;
		left = usec - current;
		if (left > 1000)
			usleep(left / 2);
		else
			while (ft_gettime(MICRO) - start < usec)
				;
	}
}

void	ft_delaying(t_philo *philo, int init)
{
	long	sleep;
	long	eat;
	long	think;

	sleep = ft_get_l(&philo->world->mtx_world, &philo->world->time_sleep);
	eat = ft_get_l(&philo->world->mtx_world, &philo->world->time_eat);
	think = eat * 1.75 - sleep;
	if (init)
		think /= 2;
	if (think < 0)
		return ;
	ft_myusleep(think, philo->world);
}
