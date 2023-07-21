/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:15:48 by acaplat           #+#    #+#             */
/*   Updated: 2023/04/28 20:06:34 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*state(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (1)
	{
		regroup(philo);
		printf("%lldms Philo %d has taken fork %d\n", how_much_time()
			- philo->rules->time, philo->id + 1, philo->l_fork_id + 1);
		printf("%lldms Philo %d has taken fork %d\n", how_much_time()
			- philo->rules->time, philo->id + 1, philo->r_fork_id + 1);
		printf("%lldms Philo %d is eating\n", how_much_time()
			- philo->rules->time, philo->id + 1);
		philo->last_meal = how_much_time();
		philo->has_eaten++;
		ft_sleep(philo->rules->time_to_eat);
		pthread_mutex_unlock(&philo->fork[philo->l_fork_id]);
		pthread_mutex_unlock(&philo->fork[philo->r_fork_id]);
		pthread_mutex_unlock(&philo->death);
		printf("%lldms Philo %d is sleeping\n", how_much_time()
			- philo->rules->time, philo->id + 1);
		ft_sleep(philo->rules->time_to_sleep);
		printf("%lldms Philo %d is thinking\n", how_much_time()
			- philo->rules->time, philo->id + 1);
	}
	return (NULL);
}

void	regroup(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork[philo->l_fork_id]);
	pthread_mutex_lock(&philo->fork[philo->r_fork_id]);
	pthread_mutex_lock(&philo->death);
}
