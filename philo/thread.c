/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:22:51 by acaplat           #+#    #+#             */
/*   Updated: 2023/04/29 13:18:14 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initialize_thread(t_philo *philo, t_rules *rules, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		philo[i].id = i;
		philo[i].l_fork_id = i;
		philo[i].r_fork_id = (i + 1) % rules->nb_philo;
		philo[i].has_eaten = 0;
		philo[i].last_meal = rules->time;
		philo[i].rules = rules;
		philo[i].fork = fork;
		if (pthread_create(&philo[i].th, NULL, &state, &philo[i]) != 0)
			return (1);
		usleep(100);
		i++;
	}
	return (0);
}

int	initialize_mutex(t_philo *philo, t_rules *rules, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&philo[i].death, NULL) != 0)
		return (1);
	while (i < rules->nb_philo)
	{
		if (pthread_mutex_init(&fork[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	thread_join(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->rules->nb_philo)
	{
		if (pthread_detach(philo[i++].th) != 0)
		{
			return (1);
		}
	}
	return (0);
}

int	check_death(t_philo *philo)
{
	int	i;

	while (1)
	{
		i = 0;
		if (is_dead(philo) == 1)
			return (1);
		while (i < philo->rules->nb_philo && philo->rules->argc == 6)
		{
			if (philo->has_eaten > philo->rules->must_eat)
			{
				philo->rules->all_eat++;
				if (philo->rules->all_eat == philo->rules->nb_philo)
				{
					printf("all philo have eaten\n");
					return (1);
				}
			}
			i++;
		}
		usleep(500);
	}
	return (0);
}

int	is_dead(t_philo *philo)
{
	if (how_much_time() - philo->last_meal > philo->rules->time_to_die)
	{
		printf("%lldms Philo %d died\n", how_much_time() - philo->rules->time,
			philo->id + 1);
		return (1);
	}
	return (0);
}
