/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src_actions_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:30:51 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/06/10 17:45:29 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_eat(t_philo *philo)
{
	ft_sem_wait(philo->world->s_fork);
	ft_write_log(FORK, philo);
	ft_sem_wait(philo->world->s_fork);
	ft_write_log(FORK, philo);
	ft_write_log(EATING, philo);
	if (philo->meals != -1)
		philo->meals--;
	philo->last_meal = ft_gettime(MILI);
	philo->next_meal = philo->last_meal + philo->die_time;
	ft_myusleep(philo->world->time_eat);
	ft_sem_post(philo->world->s_fork);
	ft_sem_post(philo->world->s_fork);
}

void	ft_sleep(t_philo *philo)
{
	ft_write_log(SLEEPING, philo);
	ft_myusleep(philo->world->time_sleep);
}

void	ft_thinking(t_philo *philo)
{
	ft_write_log(THINKING, philo);
	if (philo->impar)
		ft_delaying(philo, 0);
}

void	ft_write_log(t_life status, t_philo *philo)
{
	long	elapsed;

	elapsed = ft_gettime(MILI) - philo->world->start;
	ft_sem_wait(philo->world->s_write);
	if (FORK == status)
		printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
	else if (EATING == status)
		printf("%-6ld %d is eating\n", elapsed, philo->id);
	else if (SLEEPING == status)
		printf("%-6ld %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == status)
		printf("%-6ld %d is thinking\n", elapsed, philo->id);
	else if (DIED == status)
		printf("%-6ld %d died\n", elapsed, philo->id);
	if (status != DIED)
		ft_sem_post(philo->world->s_write);
}
