/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:54:41 by acaplat           #+#    #+#             */
/*   Updated: 2023/04/29 13:14:52 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules			rules;
	t_philo			*philo;
	pthread_mutex_t	*fork;

	if (parsing(argc, argv) == 1)
		return (printf("error not number or wrong nb of args\n"));
	initialize_rules(&rules, argc, argv);
	if (init_cond(&rules) == -1)
		return (printf("rules are broken\n"));
	rules.time = how_much_time();
	philo = malloc(sizeof(t_philo) * rules.nb_philo);
	fork = malloc(sizeof(pthread_mutex_t) * rules.nb_philo);
	if (initialize_mutex(philo, &rules, fork) == 1)
		return (printf("problem with mutex\n"));
	if (initialize_thread(philo, &rules, fork) == 1)
		return (printf("problem with init threads\n"));
	if (thread_join(philo) == 1)
		return (printf("problem with pthread_join\n"));
	if (check_death(philo) == 1)
	{
		destroy_mutex(philo, fork);
		free_all(philo, fork);
	}
	return (0);
}

int	parsing(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (argc != 5 && argc != 6)
		return (1);
	while (argv[i])
	{
		while (argv[i][j])
		{
			if (argv[i][j] >= '0' && argv[i][j] <= '9')
				j++;
			else
				return (1);
		}
		i++;
		j = 0;
	}
	return (0);
}

void	initialize_rules(t_rules *rules, int argc, char **argv)
{
	rules->argc = argc;
	rules->time = 0;
	rules->all_eat = 0;
	rules->nb_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules->must_eat = ft_atoi(argv[5]);
	else
		rules->must_eat = -1;
}

int	init_cond(t_rules *rules)
{
	if (rules->nb_philo == 0 || rules->time_to_sleep == 0
		|| rules->time_to_die == 0 || rules->time_to_eat == 0)
		return (-1);
	if (rules->argc == 6 && rules->must_eat == 0)
		return (-1);
	return (0);
}
