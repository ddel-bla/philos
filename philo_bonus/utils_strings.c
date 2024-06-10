/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:27:16 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/06/10 19:11:03 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static inline bool	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		ft_error(NULL, "Only positive numbers please.", EXIT_FAILURE);
	if (!ft_isdigit(*str))
		ft_error(NULL, "Character found. Please check input", EXIT_FAILURE);
	while (ft_isdigit(*str))
		num = (num * 10) + *str++ - '0';
	if (num > INT_MAX)
		ft_error(NULL, "INT_MAX is the max input", EXIT_FAILURE);
	return (num);
}

static size_t	ft_int_len(long i)
{
	size_t	len;

	len = 1;
	if (i < 0)
	{
		i *= -1;
		len++;
	}
	while (i > 9)
	{
		i /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(long n)
{
	char	*res;
	size_t	len;
	long	ln;

	ln = n;
	len = ft_int_len(ln);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	res[len--] = 0;
	if (ln == 0)
		res[0] = '0';
	if (ln < 0)
	{
		res[0] = '-';
		ln *= -1;
	}
	while (ln > 0)
	{
		res[len] = (ln % 10) + '0';
		ln /= 10;
		len--;
	}
	return (res);
}
