/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 00:43:32 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/05/27 00:43:32 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_gettime(t_time timecode)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		ft_error(NULL, "Gettimeofday failed", 23);
	if (MILI == timecode)
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	else
		return (tv.tv_sec * 1000000 + tv.tv_usec);
}

void	ft_myusleep(long usec)
{
	long	start;
	long	current;
	long	left;

	start = ft_gettime(MICRO);
	while (ft_gettime(MICRO)- start < usec)
	{
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

	sleep = philo->world->time_sleep;
	eat = philo->world->time_eat;
	think = eat * 1.75 - sleep;
	if (init)
		think /= 2;
	if (think < 0)
		return ;
	ft_myusleep(think);
}
