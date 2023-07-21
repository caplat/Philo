/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:51:56 by acaplat           #+#    #+#             */
/*   Updated: 2023/04/28 20:02:48 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_rules
{
	int				argc;
	int				nb_philo;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				must_eat;
	long long		time;
	int				all_eat;
}					t_rules;
typedef struct s_philo
{
	pthread_t		th;
	pthread_mutex_t	*fork;
	pthread_mutex_t	death;
	int				id;
	int				l_fork_id;
	int				r_fork_id;
	int				has_eaten;
	long long		last_meal;
	t_rules			*rules;
}					t_philo;
int					parsing(int argc, char **argv);
void				initialize_rules(t_rules *rules, int argc, char **argv);
int					ft_atoi(char *str);
int					init_cond(t_rules *rules);
long long			how_much_time(void);
void				*state(void *param);
void				ft_sleep(int t);
int					initialize_mutex(t_philo *philo, t_rules *rules,
						pthread_mutex_t *fork);
int					initialize_thread(t_philo *philo, t_rules *rules,
						pthread_mutex_t *fork);
int					thread_join(t_philo *philo);
int					check_death(t_philo *philo);
int					is_dead(t_philo *philo);
void				free_all(t_philo *philo, pthread_mutex_t *fork);
void				destroy_mutex(t_philo *philo, pthread_mutex_t *fork);
void				regroup(t_philo *philo);

#endif