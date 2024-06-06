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

#include "philo_bonus.h"

void	ft_error(t_world *world, const char *error, int numerr)
{
	printf("Error: %s\n", error);
	if (world)
		ft_exit(world);
	exit(numerr);
}

void	*ft_mymalloc(size_t bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (!ptr)
		ft_error(NULL, "Malloc issues", 11);
	return (ptr);
}

int	ft_myfork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		ft_error(NULL, "t_world *world, Fork failed", 22);
	return (pid);
}
