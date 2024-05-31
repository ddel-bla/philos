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

#include "philo.h"

long	ft_gettime(t_time timecode)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		ft_error("Gettimeofday failed");
	if (MILI == timecode)
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	else if (MICRO == timecode)
		return (tv.tv_sec * 1000000 + tv.tv_usec);
	else
		exit(123);
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
			break;
		current = ft_gettime(MICRO) - start;
		left = usec - current;
		if (left > 1000)
			usleep(left / 2);
		else
			while (ft_gettime(MICRO) - start < usec)
				;
	}
}

bool	ft_finished(t_world *world)
{
	bool ret;

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

	
	if (philo->full)
		return (0);
	elapsed = ft_gettime(MILI) - philo->last_meal;
	//printf("last    %ld\n", philo->last_meal);
	//printf("last    %ld\n", ft_gettime(MILI));
	//printf("elapsed %ld\n", elapsed);
	if (elapsed > philo->world->time_die)
		return (1);
	return (0);
}

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
