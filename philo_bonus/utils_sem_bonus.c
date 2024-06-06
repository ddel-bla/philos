/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 22:04:34 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/06/05 18:33:11 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

sem_t	*ft_sem_open(char *str, long num)
{
	sem_t	*s;

	sem_unlink(str);
	s = sem_open(str, O_CREAT, 0644, (int) num);
	if (s == SEM_FAILED)
		ft_error(NULL, "sem_open failed", 33);
	return (s);
}

void	ft_sem_wait(sem_t *sem)
{
	if (sem_wait(sem) == -1)
		ft_error(NULL, "sem_wait failed", 44);
}

void	ft_sem_post(sem_t *sem)
{
	if (sem_post(sem) == -1)
		ft_error(NULL, "sem_post failed", 55);
}

void	ft_sem_close(sem_t *sem)
{
	if (sem_close(sem) == -1)
		ft_error (NULL, "sem_close failed", 66);
}

void	ft_sem_unlink(char *sem)
{
	if (sem_unlink(sem) == -1)
		ft_error (NULL, "sem_unlink failed", 77);
}
