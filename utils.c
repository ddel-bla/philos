/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 00:43:49 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/05/27 00:43:49 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_error (const char *error)
{
	printf("Error: %s\n", error);
	exit(EXIT_FAILURE);
}

void *ft_mymalloc(size_t bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (!ptr)
		ft_error("Malloc issues");
	return (ptr);
}

int ft_myfork()
{
	int	pid;

	pid = fork();
	if (pid < 0)
		ft_error("Fork failed");
	return (pid);
}

void	ft_write_log(t_life status, t_philo *philo)
{
	long elapsed;

	elapsed = ft_gettime(MILI) - philo->world->start;
	if (philo->full)
		return ;
 	if (sem_wait(philo->world->s_write) == -1)
		ft_error("sem_wait s_write failed");
	if ((FIRST_FORK == status || SECOND_FORK == status)
		&& !ft_finished(philo->world))
		printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
	else if (EATING == status && !ft_finished(philo->world))
		printf("%-6ld %d is eating\n", elapsed, philo->id);
	else if (SLEEPING == status && !ft_finished(philo->world))
		printf("%-6ld %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == status && !ft_finished(philo->world))
		printf("%-6ld %d is thinking\n", elapsed, philo->id);
	else if (DIED == status)
		printf("%-6ld %d died\n", elapsed, philo->id);
	if (sem_post(philo->world->s_write) == -1)
		ft_error("sem_post s_write failed");
}
