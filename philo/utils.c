/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:06:43 by acaplat           #+#    #+#             */
/*   Updated: 2023/04/29 13:08:36 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (sign * result);
}

long long	how_much_time(void)
{
	struct timeval	temps;
	long long		ms;

	gettimeofday(&temps, NULL);
	ms = (temps.tv_sec * 1000) + (temps.tv_usec / 1000);
	return (ms);
}

void	ft_sleep(int t)
{
	struct timeval	b;
	struct timeval	a;

	gettimeofday(&b, NULL);
	gettimeofday(&a, NULL);
	while (((a.tv_sec - b.tv_sec) * 1000 + (a.tv_usec - b.tv_usec) / 1000) < t)
	{
		usleep(500);
		gettimeofday(&a, NULL);
	}
}

void	free_all(t_philo *philo, pthread_mutex_t *fork)
{
	free(philo);
	free(fork);
}

void	destroy_mutex(t_philo *philo, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&philo->death);
	while (i < philo->rules->nb_philo)
	{
		pthread_mutex_destroy(&fork[i]);
		i++;
	}
}
