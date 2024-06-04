/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 22:04:34 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/06/04 22:37:54 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

sem_t	*ft_sem_open(char *str, long num)
{
	sem_t	*s;

	sem_unlink(str);
	s = sem_open(str, O_CREAT, 0644, (int) num);
	if (s == SEM_FAILED)
		ft_error("sem_open failed");
	return (s);
}
